#include "ListaJugadores.h"
#include <stdlib.h>
#include <stdio.h>

//crea una lista vac�a (sin ning�n nodo)
void crear(TListaJugadores *lc){
    *lc = NULL;
}

//inserta un nuevo jugador en la lista de jugadores, poniendo 1 en el n�mero de goles marcados.
//Si ya existe a�ade 1 al n�mero de goles marcados.
void insertar(TListaJugadores *lj,unsigned int id){
    //No hay ningún jugador en la lista
    if((*lj) == NULL){
        TListaJugadores newPlayer = malloc(sizeof(struct TNode));
        if (&newPlayer == NULL){
            printf("No hay suficiente espacio en la memoria");
            exit(-1);
        }
        newPlayer -> numPlayer = id;
        newPlayer -> numGoals = 1;
        newPlayer -> nextPlayer = NULL;
        (*lj) = newPlayer;
    } else {
        //1. Hay que recorrer la lista para saber si el jugador está o no
        TListaJugadores ptr = malloc(sizeof(struct TNode));
        if (&ptr == NULL){
            printf("No hay suficiente espacio en la memoria");
            exit(-1);
        }
        ptr = (*lj);
        int is = 0;
        while (ptr != NULL && !is) {
            if(ptr -> numPlayer == id){
                is = 1;
                ptr -> numGoals++;
            }
            ptr = ptr -> nextPlayer;
        }
        if (!is){
            TListaJugadores newPlayer = malloc(sizeof(struct TNode));
            if (&newPlayer == NULL){
                printf("No hay suficiente espacio en la memoria");
                exit(-1);
            }
            newPlayer -> numPlayer = id;
            newPlayer -> numGoals = 1;
            if (id < (*lj) -> numPlayer){
                newPlayer -> nextPlayer = (*lj);
                (*lj) = newPlayer;
            } else {
                ptr = (*lj);
                while (ptr -> nextPlayer != NULL && ptr -> nextPlayer -> numPlayer < id){
                    ptr = ptr -> nextPlayer;
                }
                newPlayer -> nextPlayer = ptr -> nextPlayer;
                ptr -> nextPlayer = newPlayer;
            }
        }
    }
}

//recorre la lista circular escribiendo los identificadores y los goles marcados
void recorrer(TListaJugadores lj){
    while (lj != NULL){
        printf("El jugador %d lleva %d gol/es marcados.\n", lj -> numPlayer, lj -> numGoals);
        lj = lj -> nextPlayer;
    }
}

//devuelve el n�mero de nodos de la lista
int longitud(TListaJugadores lj){
    int num = 0;
    while (lj != NULL){
        num++;
        lj = lj -> nextPlayer;
    }
    return num;
}

//Eliminar. Toma un n�mero de goles como par�metro y
//elimina todos los jugadores que hayan marcado menos que ese n�mero de goles
void eliminar(TListaJugadores *lj,unsigned int n){
    TListaJugadores ptr = malloc(sizeof(struct TNode));
    if (&ptr == NULL){
        printf("No hay suficiente espacio en la memoria");
        exit(-1);
    }
    ptr = (*lj);
    while (ptr != NULL && ptr -> numGoals < n){
        (*lj) = ptr -> nextPlayer;
        free(ptr);
        ptr = (*lj);
    }
    if (ptr != NULL){
        while (ptr -> nextPlayer != NULL){
            if (ptr -> nextPlayer -> numGoals < n){
                TListaJugadores aux = malloc(sizeof(struct TNode));
                if (&aux == NULL){
                    printf("No hay suficiente espacio en la memoria");
                    exit(-1);
                }
                aux = ptr -> nextPlayer;
                ptr -> nextPlayer = aux -> nextPlayer;
                free(aux);
            }
            ptr = ptr -> nextPlayer;
        }
    }
}


// Devuelve el ID del m�ximo jugador. Si la lista est� vac�a devuelve 0. Si hay m�s de un jugador con el mismo n�mero de goles que el m�ximo devuelve el de mayor ID
// Hay que devolver el identificador, no el n�mero de goles que ha marcado
unsigned int maximo(TListaJugadores lj){
    if (lj == NULL){
        return 0;
    } else {
        TListaJugadores res = malloc(sizeof(struct TNode));
        if (&res == NULL){
            printf("No hay suficiente espacio en memoria.");
            exit(-1);
        }
        res = lj;
        lj = lj -> nextPlayer;
        while(lj != NULL){
            if (lj -> numGoals > res -> numGoals){
                res = lj;
            } else if (lj -> numGoals == res -> numGoals){
                if (lj -> numPlayer > res -> numPlayer){
                    res = lj;
                }
            }
            lj = lj -> nextPlayer;
        }
        return res -> numPlayer;
    }
}

//Destruye la lista y libera la memoria)
void destruir(TListaJugadores *lj){
    TListaJugadores ptr = malloc(sizeof(struct TNode));
    if (&ptr == NULL){
        printf("No hay suficiente espacio en la memoria");
        exit(-1);
    }
    ptr = (*lj);
    while (ptr != NULL){
        (*lj) = ptr -> nextPlayer;
        free(ptr);
        ptr = (*lj);
    }
}

