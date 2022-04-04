#include <stdio.h>
#include <stdlib.h>

typedef struct T_Hebra *LHebra;

struct T_Hebra{
    char *id;
    int priority;
    LHebra next;
};

typedef struct T_Process *LSistema;

struct T_Process {
    int id;
    LHebra hebras;
    LSistema next;
};

void Crear (LSistema *ls){
    *ls = NULL;
}

void InsertarProceso (LSistema *ls, int idproc) {
    LSistema newNode = malloc(sizeof(struct T_Process));
    newNode -> id = idproc;
    newNode -> next = NULL;
    newNode -> hebras = NULL;
    if (*ls == NULL){
        //La lista está vacía
        *ls = newNode;
    } else {
        LSistema ptr = (*ls);
        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = newNode;
    }
}

void InsertarHebra (LSistema *ls, int idproc, char *idhebra, int priohebra ){
    if (*ls == NULL){
        printf("No se pueden insertar hebras debido a que no hay procesos");
    } else {
        LSistema ptr = (*ls);
        while (ptr != NULL && ptr -> id != idproc){
            ptr = ptr -> next;
        }
        if (ptr == NULL){
            printf("No se ha encontrado el proceso");
        } else {
            LHebra newHebra = malloc(sizeof(struct T_Hebra));
            LHebra *lista = &(ptr -> hebras);
            newHebra -> id = idhebra;
            newHebra -> priority = priohebra;
            if (*lista == NULL){
            //La lista está vacía
                *lista = newHebra;
            } else {
                LHebra ptr_hebra = (*lista);
                //Insertar al principio
                if (newHebra -> priority > ptr_hebra -> priority){
                    newHebra -> next = (*lista);
                    *lista = newHebra;
                } else {
                    while (ptr_hebra -> next != NULL && newHebra -> priority < ptr_hebra -> next -> priority){
                        ptr_hebra = ptr_hebra -> next;
                    }
                    if (ptr_hebra -> next == NULL){
                        newHebra -> next = NULL;
                        ptr_hebra -> next = newHebra;
                    } else {
                        newHebra -> next = ptr_hebra -> next;
                        ptr_hebra -> next = newHebra;
                    }
                }
            }
        }
    }
}

void Mostrar (LSistema ls){
    if (ls == NULL){
        printf("No hay procesos");
    } else {
        while (ls != NULL){
            printf("El proceso es -> %d y ", ls -> id);
            if (ls -> hebras == NULL) {
                printf("no tiene hebras");
            } else {
                printf("y sus hebras son: ");
                LHebra ptr_hebras = ls -> hebras;
                while (ptr_hebras != NULL){
                    printf("%s ", ptr_hebras -> id);
                    ptr_hebras = ptr_hebras -> next;
                }
            }
            ls = ls -> next;
            printf("\n");
        }
    }
}

void EliminarProc (LSistema *ls, int idproc){
    if ((*ls) != NULL){
        LSistema aux = (*ls);
        if ((*ls) -> id == idproc){
            (*ls) = (*ls) -> next;
            free(aux);
        } else {
            while (aux -> next != NULL && aux -> next -> id != idproc){
                aux = aux -> next;
            }
            LSistema elemBorrar = aux -> next;
            aux -> next = elemBorrar -> next;
            BorrarHebras(&(elemBorrar -> hebras));
            free(elemBorrar);
        }
    }
}

void BorrarHebras (LHebra *hebra){
    while ((*hebra) != NULL){
        LHebra aux = (*hebra);
        (*hebra) = (*hebra) -> next;
        free(aux);
    } 
}

void Destruir (LSistema *ls){
    while ((*ls) != NULL){
        LSistema aux = (*ls);
        (*ls) = (*ls) -> next;
        BorrarHebras(&(aux -> hebras));
        free(aux);
    }
}

int main(){
    LSistema ls;
    Crear(&ls);
    InsertarProceso(&ls, 4);
    InsertarProceso(&ls, 6);
    InsertarProceso(&ls, 1);
    InsertarProceso(&ls, 2);
    InsertarProceso(&ls, 3);
    InsertarProceso(&ls, 5);
    InsertarHebra(&ls, 6, "h1", 7);
    InsertarHebra(&ls, 6, "h2", 4);
    InsertarHebra(&ls, 6, "h3", 1);
    InsertarHebra(&ls, 2, "h5", 2);
    InsertarHebra(&ls, 2, "h7", 10);
    InsertarHebra(&ls, 2, "h8", 3);
    EliminarProc(&ls, 3);
    Destruir(&ls);
    Mostrar(ls);
    return 0;
}
