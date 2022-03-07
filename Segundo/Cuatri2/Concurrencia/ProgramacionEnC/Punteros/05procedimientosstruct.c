/*
1.- Define la siguiente extructura:
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

Define una función incrementarPrecio, que recive como parámetros una estructura str_Libro, y un float incr, y devuelve una nueva str_Libro con el mismo contenido pero su precio incrementado incr.

¿Se pasa por valor o por referencia el parámetro de la estructura?

2.- Cambia la función anterior y conviértela para que se pase por referencia la estructura y no se requiera copiar.

*/
#include <stdio.h>
#include <string.h>

struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

void incrementarPrecio (struct str_Libro *str, float incr){
    str -> precio += incr;
}

int main ()
{
    struct str_Libro libro;
    strcpy(libro.autor, "ErJaki");
    strcpy(libro.titulo, "Tears of my Student");
    libro.paginas = 12;
    libro.precio = 10.5;
    incrementarPrecio(&libro, 10.0);
    return 0;
}
