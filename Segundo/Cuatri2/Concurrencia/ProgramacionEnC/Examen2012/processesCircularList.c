#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Definimos la estructura de la lista
//En primer lugar tenemos que crear una estructura para cada nodo de la lista
typedef struct T_Node *LProc;

struct T_Node {
    int proceso;
    LProc next;
};



//Ahora debemos definir los metodos de la estructura
//Crea una lista de procesos vacia
void Crear(LProc *lista){
    *lista = NULL;
}

//Añade un proceso con el identificador idproc y se añade anterior al proceso que se está ejecutando
void AñadirProceso(LProc *lista, int idproc){
    LProc newNode = malloc(sizeof(struct T_Node));
    if (newNode == NULL){
        perror("No se ha podido obtener la memoria indicada");
        exit(-1);
    }
    newNode -> proceso = idproc;
    if (*lista == NULL){
        //Voy a indicar que solo hay un proceso indicando que el siguiente es nulo
        newNode -> next = NULL;
        *lista = newNode;
    } else {
        newNode -> next = (*lista);
        //Caso en el que hay un solo elemento
        if ((*lista) -> next == NULL){
            (*lista) -> next = newNode;
        } else{
            //Caso en el que hay más de un elemento
            //Nos movemos al último elemento
            LProc ptr = (*lista);
            while (ptr -> next -> proceso != (*lista) -> proceso){
                ptr = ptr -> next;
            }
            ptr -> next = newNode;
        }
    }
}

//Muestra la lista de procesos disponibles para ejecución
void MostrarLista (LProc lista){
    if (lista != NULL){
        if (lista -> next == NULL){
            printf("%i", lista -> proceso);
        } else {
            int first = lista -> proceso;
            while (lista -> next != NULL && lista -> next -> proceso != first){
                printf("%i ", lista -> proceso);
                lista = lista -> next;
            }
            printf("%i \n", lista -> proceso);
        }
    } else {
        printf("No hay procesos en la lista\n");
    }
}

//Simula la ejecución de un proceso eliminándolo de la lista
void EjecutarProceso(LProc *lista){
    if (*lista != NULL){
        if ((*lista) -> next == NULL || ((*lista) -> next -> proceso == (*lista) -> proceso)){
            (*lista) = NULL;
            *lista = NULL;
        } else {
            LProc aux = malloc(sizeof(struct T_Node));
            if (aux == NULL){
                perror("No se ha podido obtener la memoria deseada");
                exit(-1);
            }
            //me muevo al ultimo elemento y le digo que el siguiente es el que va despues del primero
            aux = (*lista);
            while (aux -> next -> proceso != (*lista) -> proceso){
                aux = aux -> next;
            }
            aux -> next = (*lista) -> next;
            aux = (*lista);
            (*lista) = (*lista) -> next;
            free(aux);
        }
    }
}

int main(){
    LProc lista;
    Crear(&lista);
    MostrarLista(lista);
    AñadirProceso(&lista, 1);
    assert(lista -> proceso == 1);
    AñadirProceso(&lista, 5);
    assert(lista -> next -> proceso == 5);
    AñadirProceso(&lista, 3);
    assert(lista -> next -> next -> proceso == 3);
    MostrarLista(lista);
    EjecutarProceso(&lista);
    assert(lista -> proceso == 5);
    MostrarLista(lista);
    EjecutarProceso(&lista);
    assert(lista -> proceso == 3);
    MostrarLista(lista);
    AñadirProceso(&lista, 2);
    MostrarLista(lista);
    return 0;
}