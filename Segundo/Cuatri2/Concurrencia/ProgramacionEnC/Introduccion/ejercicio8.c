/*
Copia la siguiente extructura:
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};
1.- Vamos a definir las variables tras la definición de la estructura.
2.- ¿Puedes generar un libro y mostrar sus datos en consola?
3.- Vamos a crear un nuevo tipo de datos, el Libro.
4.- Vamos a definir variables con la definición de la estructura.

*/
#include<stdio.h>
#include<string.h>
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

typedef struct str_Libro Libro;

int main(int argc, char const *argv[])
{
    struct str_Libro libro;
    Libro libro1;

    strcpy(libro.autor,"Joaquin Ballesteros");
    libro.precio= 15;
    printf("Titulo: %s\nAutor: %s\nPrecio %f euros",libro.titulo,libro.autor,libro.precio);    
    return 0;
}
