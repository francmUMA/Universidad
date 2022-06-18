#include "colaprio.h"
#include <stdio.h>
#include <stdlib.h>

void add_proc(TColaPrio *cola, int info[]) {
    TColaPrio newElem = malloc(sizeof(struct PNodo));
    newElem -> pid = info[0];
    newElem -> prioridad = info[1];
    if (*cola == NULL) {
        newElem -> sig = NULL;
        (*cola) = newElem;
    } else {
        if (newElem -> prioridad <= (*cola) -> prioridad) {
            newElem -> sig = (*cola);
            (*cola) = newElem;
        } else {
            TColaPrio aux = (*cola);
            while (aux -> sig != NULL && newElem -> prioridad > aux -> sig -> prioridad) {
                aux = aux -> sig;
            }
            newElem -> sig = aux -> sig;
            aux -> sig = newElem;
        }
    }
}

void Crear_Cola(char *nombre, TColaPrio *cp){
    *cp = NULL;
    FILE *file = fopen(nombre, "rb");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        exit(-1);
    }
    int numProcesos;
    fread(&numProcesos, sizeof(int), 1, file);
    int info[2];
    while (fread(info, sizeof(int), 2, file) == 2) add_proc(cp, info);
}

void Mostrar(TColaPrio cp){
    //Mostrar todos los elementos de la cola
    while (cp != NULL){
        printf("%d %d", cp -> pid, cp -> prioridad);
        if (cp -> sig != NULL) printf(" -> ");
        cp = cp -> sig;
    }
}

void Destruir(TColaPrio *cp){
    while (*cp != NULL){
        TColaPrio aux = (*cp);
        (*cp) = (*cp) -> sig;
        free(aux);
        
    }
}

void Ejecutar_Max_Prio(TColaPrio *cp){
    Ejecutar(cp, (*cp) -> prioridad);
}

void Ejecutar(TColaPrio *cp, int prio){
    TColaPrio aux = (*cp);
    if (aux != NULL && aux -> sig == NULL){
        if (aux -> prioridad == prio) {
            free(aux);
            *cp = NULL;
        }
    } else if (aux != NULL && aux -> sig != NULL){
        TColaPrio auxSig = aux -> sig;
        //Hay eliminar los primeros elementos de la cola porque es prio es igual a prioridad
        if (aux -> prioridad == prio) {
            while (aux != NULL && aux -> prioridad == prio) {
                TColaPrio eliminar = aux;
                aux = auxSig;
                auxSig = auxSig -> sig;
                free(eliminar);
                (*cp) = aux;
            }
        } else {
            //Hay que eliminar elementos de la cola ya que no hay es la maxima prioridad
            while(auxSig != NULL && auxSig -> prioridad < prio){
                aux = auxSig;
                auxSig = aux -> sig;
            }
            while (auxSig != NULL && auxSig -> prioridad == prio) {
                TColaPrio eliminar = auxSig;
                aux -> sig = auxSig -> sig;
                auxSig = auxSig -> sig;
                free(eliminar);
            }
        }
    }
    
}