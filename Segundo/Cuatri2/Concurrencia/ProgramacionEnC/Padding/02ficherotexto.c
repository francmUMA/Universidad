#include<stdio.h>
#include<stdlib.h>
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
1.- Crea un fichero que se va a abrir (fopen) en modo texto y escritura con un parámetro de entrada de la línea de comandos argv[1]. El argv[0] es el nombre del propio programa.
https://www.cplusplus.com/reference/cstdio/fopen/

Ejecuta varias veces el programa y observa si cambia el fichero.

2.- Cambia el modo de acceso del fichero de escritura "w" a añadir "a", ¿qué resultado se espera?

Ejecuta varias veces el programa y observa si cambia el fichero.

3.- Ahora vamos a pasar los parámetros con args en el launch.json. 
https://code.visualstudio.com/docs/cpp/launch-json-reference#_environment

4.- COmo curiosidad, mira el puntero al fichero, tiene unos cuantos campos interesantes.
http://tigcc.ticalc.org/doc/stdio.html#FILE

¿Cuántos bytes podemos escribir como máximo? 
*/

int main(int argc, char const *argv[])
{

    if (argc!=2){
        printf("Se esperaban el nombre de fichero como parámetro de entrada");
        exit(-1);
    }

    FILE * ptr_file;
    if ((ptr_file=fopen(argv[1],"a")) == NULL){
        perror("error al abrir el fichero");
        exit(-1);
    }

    //Creamos datos para jugar
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


    ptr_str_union_item iterator = lista;
    while(iterator!=NULL){
        printf("tipo %c,Titulo %s, precio %.2f\n",iterator->tipo,(iterator->tipo=='r'?iterator->item.revista.titulo:iterator->item.libro.titulo),(iterator->tipo=='r'?iterator->item.revista.precio:iterator->item.libro.precio));
        fprintf(ptr_file, "tipo %c,Titulo %s, precio %.2f\n",iterator->tipo,(iterator->tipo=='r'?iterator->item.revista.titulo:iterator->item.libro.titulo),(iterator->tipo=='r'?iterator->item.revista.precio:iterator->item.libro.precio));
        iterator=iterator->siguiente;
    }
    fclose(ptr_file);
    return 0;
}
