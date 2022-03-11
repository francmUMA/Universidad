#include <stdlib.h>
#include <stdio.h>
#include "gestion_lista.h"

//crea una lista vacía
void crearLista(Lista *l){
    Lista node = malloc(sizeof(struct NodoLista));
    if (node == NULL){
        perror("Malloc memory fail");
        exit(-1);
    } else {
        node = NULL;
        *l = node;
    }
} 
 //escribe en la pantalla los elementos de la lista
void recorrerLista(Lista l){
    Lista ptr = l;
    while (ptr != NULL){
        printf("%u ", ptr -> elem);
        ptr = ptr -> sig;
    }
} 

//devuelve 0 sii la lista está vacía
int listaVacia(Lista l){
    return !(l == NULL);
}  

// inserta el elemento elem en la lista l de forma que quede ordenada de forma creciente
void insertarLista(Lista *l,int elem){
    Lista node = malloc(sizeof(struct NodoLista));
    if (node == NULL){
        perror("malloc memory fail");
        exit(-1);
    } else {
        node -> elem = elem;
        Lista aux = (*l);
        
        //Si hay que insertar al principio
        if ((aux != NULL && aux -> elem >= elem) || (aux == NULL)){
            node -> sig = aux;
            *l = node;
        } else {
            //El elemento se introduce en el medio o al final
            while (aux -> sig != NULL && aux -> sig -> elem < elem){
                aux = aux -> sig;
            }
            node -> sig = aux -> sig;
            aux -> sig = node;
        }
    }
}   

// elimina de la lista el elemento elem. Devuelve 1 si se ha podido eliminar y 0, si elem no estaba en la lista.
int extraerLista(Lista *l,int elem){
    Lista aux = (*l);
    if (aux != NULL){
        if (aux -> elem == elem){
            *l = aux -> sig;
            return 1;
        } else {
            while (aux -> sig != NULL && aux -> sig -> elem < elem){
                aux = aux -> sig;
            }
            if (aux -> sig == NULL){
                return 0;
            } else {
                if (aux -> sig -> elem > elem) {
                    return 0;
                } else {
                    aux -> sig = aux -> sig -> sig;
                    return 1;
                }
            }
        }
    } else {
        return 0;
    }
}   

 //elimina todos los nodos de la lista y la deja vacía
void borrarLista(Lista *l){
    Lista aux = (*l);
    while (aux != NULL){
        (*l) = (*l) -> sig;
        free(aux);
        aux = (*l);
    }
    (*l) = NULL;
}  
