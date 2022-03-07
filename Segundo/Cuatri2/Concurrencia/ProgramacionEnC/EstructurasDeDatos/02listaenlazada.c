#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

enum Meses { ENE, FEB, MAR, ABR, MAY, JUN, JUL, AGO, SEP, OCT, NOV, DIC };

struct str_Revisa_Mensual
{
    char titulo[200];
    enum Meses mes;
    float precio;
};

union u_Item{
    struct str_Libro libro;
    struct str_Revisa_Mensual revista;
};

typedef struct str_union_item * ptr_str_union_item;

struct str_union_item{
    union u_Item item;
    char tipo;
    ptr_str_union_item siguiente;  
};

/*
1- Se proporciona el código para rellenar tres item de esa lista enlazada. Recorrela haciendo uso de un bucle while para mostrar con printf el tipo y el precio.

2- Se proporciona el código para rellenar tres item de esa lista enlazada. Recorrela haciendo uso de un bucle while para mostrar con printf el tipo y el precio y para tras mostrar la primera revista. 

3.-Prueba a preguntar por un tipo que no exista, ¿importa el orden en el que se pregunta la condición? ¿Debe ir siempre primero el preguntar si el puntero es no NULO?

*/
int main(int argc, char const *argv[])
{
    ptr_str_union_item lista = malloc(sizeof(struct str_union_item));
    (*lista).tipo='l';
    strcpy(lista->item.libro.titulo,"HOla mundo book");
    strcpy(lista->item.libro.autor,"Joaquin Ballesteros");
    lista->item.libro.paginas=100;
    lista->item.libro.precio=25.5;

    lista->siguiente= malloc(sizeof(struct str_union_item));
    lista->siguiente->tipo='l';
    strcpy(lista->siguiente->item.libro.titulo,"Hi there budy");
    strcpy(lista->siguiente->item.libro.autor,"Carlos Bustamante");
    lista->siguiente->item.libro.paginas=50;
    lista->siguiente->item.libro.precio=15.5;

    lista->siguiente->siguiente= malloc(sizeof(struct str_union_item));
    lista->siguiente->siguiente->tipo='r';
    strcpy(lista->siguiente->siguiente->item.revista.titulo,"Marca gol");
    lista->siguiente->siguiente->item.revista.mes=1;
    lista->siguiente->siguiente->item.revista.precio=3.5;
    lista->siguiente->siguiente->siguiente=NULL;


    ptr_str_union_item ptr = lista;
    while(ptr != NULL && ptr -> tipo != 'k'){
        printf("Titulo %s, precio %.2f\n",
        (ptr->tipo=='r'?ptr->item.revista.titulo:ptr->item.libro.titulo),
        (lista->tipo=='r'?ptr->item.revista.precio:ptr->item.libro.precio));
        ptr = ptr -> siguiente;
    }
    return 0;
}
