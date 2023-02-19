#include <stdio.h>
#include <stdlib.h>


typedef struct node* Lista;

struct node {
    union { char dato[32];          // operando o resultado para hexadecimal
            char dato_binario[32];  // cadena para almacenar el operando/resultado binario
            char operacion[10];     // cadena descriptiva de la operacion
          } contenido;
    Lista siguiente;
} node;

void create_list(Lista *list){
    Lista newlist = malloc(sizeof(node));
    if (newlist == NULL){
        perror("Malloc memory fail");
        exit(-1);
    } else {
        newlist = NULL;
        *list = newlist;
    }
}

void add_operand();

void add_binary();

void add_hex();

void delete_node();

void print_memory(Lista list){

}


