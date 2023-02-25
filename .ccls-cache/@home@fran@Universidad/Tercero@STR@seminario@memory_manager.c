#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* Lista;

struct node {
    union { char dato[32];          // operando o resultado para hexadecimal
            char dato_binario[32];  // cadena para almacenar el operando/resultado binario
            char operacion[10];     // cadena descriptiva de la operacion
          } contenido;
    Lista siguiente;
} node;

void create_list(Lista *list){
    *list = NULL;    
}

void add_node(char *opr, Lista *list, char elem){

    //Creación de nodo
    Lista new_node = malloc(sizeof(node));
    if (elem == '0') {
        strcpy(new_node -> contenido.operacion, opr);
    } else if (elem == '1'){
        strcpy(new_node -> contenido.dato_binario, opr);
    } else {
        strcpy(new_node -> contenido.dato, opr);

    }
    new_node -> siguiente = NULL;

    //Añadir el nodo
    if ((*list) == NULL){
        *list = new_node;
    } else {
        Lista aux = (*list);
        while (aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = new_node;
    } 
}


void delete_node();

void print_memory(Lista list){
    while (list != NULL) {
        printf("%s ", list -> contenido.dato);
        list = list -> siguiente;
    }
}


