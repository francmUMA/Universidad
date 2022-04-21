#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Inicializa la lista de puntos creando una lista vacía
 *
 */
void crearLista(TLista *lista){
    *lista = NULL;
}


/**
 * Inserta el punto de forma ordenada (por el valor de la abscisa x)
 * en la lista siempre que no esté repetida la abscisa.
 *  En ok, se devolverá un 1 si se ha podido insertar, y  0 en caso contrario.
 *  Nota: utiliza una función auxiliar para saber
 *   si ya hay un punto en la lista con la misma abscisa punto.x
 *
 */
void insertarPunto(TLista *lista, struct Punto punto, int * ok){
    *ok = 1;
    if (*lista == NULL){
        TLista newNode = malloc (sizeof(struct Nodo));
        if (newNode == NULL){
            printf("No se ha podido pedir memoria");
            *ok = 0;
            exit(-1);
        }
        newNode -> punto = punto;
        newNode -> sig = NULL;
        (*lista) = newNode;
    } else {
        //Hay que comprobar que no este en la lista
        TLista ptr = (*lista);
        while (ptr != NULL && *ok){
            if (ptr -> punto.x == punto.x){
                *ok = 0;
            }
            ptr = ptr -> sig;
        }
        if (*ok){
            //No hay un elemento con dicha coordenada x
            TLista newNode = malloc (sizeof(struct Nodo));
            if (newNode == NULL){
                printf("No se ha podido pedir memoria");
                *ok = 0;
                exit(-1);
            }
            newNode -> punto = punto;

            //Hay que introducirlo al inicio
            if (punto.x < (*lista) -> punto.x){
                newNode -> sig = (*lista);
                (*lista) = newNode;
            } else {
                //Hay que introducirlo en el medio
                ptr = (*lista);
                while(ptr -> sig != NULL && punto.x > ptr -> sig -> punto.x){
                    ptr = ptr -> sig;
                }
                newNode -> sig = ptr -> sig;
                ptr -> sig = newNode;
            }
        }
    }
}


/*
 * Elimina de la lista el punto con abscisa x de la lista.
 * En ok devolverá un 1 si se ha podido eliminar,
 * y un 0 si no hay ningún punto en la lista con abscisa x
 *
 */
void eliminarPunto(TLista *lista,float x,int* ok){
    *ok = 0;
    if (*lista != NULL){
        TLista ptr = (*lista);
        if ((*lista) -> punto.x == x){
            (*lista) = (*lista) -> sig;
            free(ptr);
            *ok = 1;
        } else {
            while (ptr -> sig != NULL && x != ptr -> sig -> punto.x){
                ptr = ptr -> sig;
            }
            if (ptr -> sig != NULL){
                TLista aux = ptr -> sig;
                ptr -> sig = ptr -> sig -> sig;
                free(aux);
                *ok = 1;
            } 
        }
    }
}


 /**
 * Muestra en pantalla el listado de puntos
 */
void mostrarLista(TLista lista){
    while (lista != NULL){
        printf("x: %f  y: %f \n", lista -> punto.x, lista -> punto.y);
        lista = lista -> sig;
    }
    printf("-------------------------------------------------------\n");
}

/**
 * Destruye la lista de puntos, liberando todos los nodos de la memoria.
 */
void destruir(TLista *lista){
    while (*lista != NULL){
        TLista aux = (*lista);
        (*lista) = (*lista) -> sig;
        free(aux);
    }
}

/*
 * Lee el contenido del archivo binario de nombre nFichero,
 * que contiene una secuencia de puntos de una función polinómica,
 *  y lo inserta en la lista.
 *
 */
void leePuntos(TLista *lista,char * nFichero){
    FILE *file = fopen(nFichero, "rb");
    crearLista(lista);
    if (file == NULL){
        printf("No se ha podido abrir el fichero");
        exit(-1);
    }
    float coords[2];
    while (fread(&coords, sizeof(float), 2, file) == 2){
        struct Punto p;
        p.x = coords[0];
        p.y = coords[1];
        int ok;
        insertarPunto(lista, p, &ok);
    }
    fclose(file);
}