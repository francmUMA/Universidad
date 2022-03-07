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
Se ha definido un elemnto que tiene un libro o una revista, un tipo y un puntero a otro elemento igual que el que se ha definido.

La gestión de memoria dinámica se realiza con dos funciones:

1) Una para pedir memoria, malloc, en la que se indica el número de bytes que necesitamos, por ejemplo sizeof(struct str_union_item) bytes, y nos devuelve un puntero a una zona de memoria que contiene el espacio requerido, o NULL, si no ha podido asignar memoria.

2) Una para liberar la memoria a la que apunta un puntero, free.

*/

/*
1- Declara una variable lista de tipo puntero a str_union_item (ptr_str_union_item) en main. Pide memoria para ella y rellena sus datos:
*/ 
int main ()
{
    ptr_str_union_item lista = malloc(sizeof(struct str_union_item));
    (*lista).tipo='1';
    strcpy(lista->item.libro.titulo,"HOla mundo book");
    strcpy(lista->item.libro.autor,"Joaquin Ballesteros");
    lista->item.libro.paginas=100;
    lista->item.libro.precio=25.5;
    lista->siguiente=NULL;
    while(1){
        if (lista != NULL){
            lista = (ptr_str_union_item) malloc(sizeof(struct str_union_item));
            (*lista).tipo = 'l';
            strcpy(lista -> item.libro.titulo, "Hola mundo book");
            strcpy(lista -> item.libro.autor, "Joaquin Ballesteros");
            lista -> item.libro.paginas = 100;
            lista -> item.libro.precio += 1;
            lista -> siguiente = NULL;
            free(lista);
        } else perror("No hay memoria");
    }
}
/*
¿Inicializa los datos malloc? usa el debug.

2.- Genera un bucle infinito, que pide memoria para lista e incrementa el precio en 1 euro. ¿se puede detectar que no estamos liberando memoria? Mira los procesos del sistema...

3.- Usa free para liberar memoria.

*/
