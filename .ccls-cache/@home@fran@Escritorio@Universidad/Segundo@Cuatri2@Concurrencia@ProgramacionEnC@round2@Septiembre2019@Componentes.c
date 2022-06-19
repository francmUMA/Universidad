#include "Componentes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista){
    if (lista == NULL)
        return 1;
    else
        return 0;
}

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista  lista){
    int num = 0;
    Lista aux = lista;
    while (aux != NULL){
        num++;
        aux = aux->sig;
    }
    return num;
}

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduzca el codigo del componente: ");
    scanf("%ld",codigo);
    printf("Introduzca el texto del componente: ");
    scanf("%s",texto);
}

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista){
    Lista aux = lista;
    while (aux != NULL){
        printf("%ld %s\n",aux->codigoComponente,aux->textoFabricante);
        aux = aux->sig;
    }
}

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar( Lista  lista){
    FILE *fichero;
    Lista aux = lista;
    fichero = fopen("examen.dat","wb");
    while (aux != NULL){
        fwrite(aux,sizeof(Componente),1,fichero);
        aux = aux->sig;
    }
    fclose(fichero);
}


/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear(){
    return NULL;
}

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista nuevo = malloc(sizeof(Componente));
    nuevo->codigoComponente = codigo;
    strcpy(nuevo->textoFabricante,textoFabricante);
    nuevo->sig = NULL;
    if (*lista == NULL){
        *lista = nuevo;
    }
    else{
        Lista aux = (*lista);
        while (aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista){
    Lista aux = *lista;
    if (aux != NULL){
        if (aux->sig == NULL){
            free(aux);
            *lista = NULL;
        }
        else{
            while (aux->sig->sig != NULL){
                aux = aux->sig;
            }
            free(aux->sig);
            aux->sig = NULL;
        }
    }
}

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista){
    Lista aux = *lista;
    while (aux != NULL){
        Lista aux2 = aux->sig;
        free(aux);
        aux = aux2;
    }
    *lista = NULL;
}


