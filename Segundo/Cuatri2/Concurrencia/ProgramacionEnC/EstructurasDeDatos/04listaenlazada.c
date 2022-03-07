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
1- Se proporciona el código para rellenar tres item de esa lista enlazada. ¿Cómo se puede insertar un nuevo elemento al principio de la lista? 

2.-Comenta el código anterior y prueba ahora, a insertarlo al final.

3. Ahora queremos mantener todos los libros al principio y las revistas al final de la lista. Prueba a generar dos punteros para recorrer la lista e insertar en el sitio que corresponde, antes de la primera revista. Ojo, que la lista podría estar vacía o podría contener sólo revistas.

*/
int main ()
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


   //-------------
    ptr_str_union_item nuevo_elemento = malloc(sizeof(struct str_union_item));
    nuevo_elemento->tipo='l';
    strcpy(nuevo_elemento->item.libro.titulo,"Book nuevo");
    strcpy(nuevo_elemento->item.libro.autor,"Joaquin Cabagho");
    nuevo_elemento->item.libro.paginas=11;
    nuevo_elemento->item.libro.precio=12.5;
    nuevo_elemento->siguiente=NULL;
    return 0;
}
