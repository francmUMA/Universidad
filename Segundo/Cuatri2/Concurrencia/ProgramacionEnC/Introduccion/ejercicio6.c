/*
Enunciado: Vamos a hacer el esqueleto de un menú interactivo.
El usuario introduce una cadena de texto inferior a 100 carácteres que representa una de las siguientes opciones de menú: 

iniciar
llamada1
llamada2
fin

Tras leer, imprimimos un mensaje, elige el mensaje que quieras. Cuando se lee un fin, se termina el programa. Si se lee algo que no corresponde con una opción de menú, se avisa al usuario que no se conoce esa opción, y se le
muestra lo que ha introducido.
*/

#include <stdio.h>
#include <string.h>
int main()
{
    char cadena[100];
    printf("Introduce una operacion: ");
    scanf("%s", cadena);
    if (strcmp(cadena, "iniciar") == 0){
       printf("Se ha iniciado el programa"); 
    } else if(strcmp(cadena, "llamada1") == 0){
        printf("Se ha realizado la llamada1");
    } else if (strcmp(cadena, "llamada2") == 0) {
        printf("Se ha realizado la llamada2");
    } else if (strcmp(cadena, "fin") == 0){
        printf("Se ha terminado el programa"); 
    } else {
        printf("Has introducido una operacion erronea: %s", cadena);
    }
}
