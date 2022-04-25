#include "Componentes.h"
#include <stdio.h>
#include <stdlib.h>

/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista){
    if (lista == NULL){
        return 1;
    } else {
        return 0;
    }
}

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista  lista){
    int res = 0;
    while (lista != NULL){
        lista = lista -> sig;
        res++;
    }
    return res;
}

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduzca el codigo y el texto: ");
    scanf("%ld", codigo);
    fgets(texto, MAX_CADENA, stdin);
}

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista){
    while (lista != NULL){
        printf("Codigo: %ld Texto: %s", lista -> codigoComponente, lista -> textoFabricante);
        lista = lista -> sig;
    }
}

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar(Lista  lista){
    FILE *file = fopen("examen.dat", "wb");
    while (lista != NULL){
        fwrite(lista, sizeof(Componente), 1, file);
        lista = lista -> sig;
    }
    fclose(file);
}


/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear(){
    Lista newLista = NULL;
    return newLista;
}

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista newNode = malloc (sizeof(Componente));
    if (newNode == NULL){
        perror("No hay suficiente memoria");
        exit(-1);
    }
    newNode -> codigoComponente = codigo;
    strcpy(newNode -> textoFabricante, textoFabricante);
    newNode -> sig = NULL;
    if ((*lista) != NULL){
        Lista ptr = (*lista);
        while (ptr -> sig != NULL)
        {
            ptr = ptr -> sig;
        }
        ptr -> sig = newNode;
    } else {
        *lista = newNode;
    }
}

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista){
    if ((*lista) != NULL){
        if ((*lista) -> sig == NULL){
            free((*lista));
            *lista = NULL;
        } else {
            Lista ptr = (*lista);
            Lista ptr_ant;
            while (ptr -> sig != NULL){
                ptr_ant = ptr;
                ptr = ptr -> sig;
            }
            free(ptr);
            ptr_ant -> sig = NULL; 
        }
        
    }
}

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista){
    while ((*lista) != NULL){
        Lista aux = (*lista);
        (*lista) = (*lista) -> sig;
        free(aux);
        aux = NULL;
    }
    *lista = NULL;
}