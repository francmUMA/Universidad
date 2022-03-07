/*
Enunciado: Vamos a hacer el esqueleto de un menú interactivo.
El usuario introduce un carácter que representa una de las siguientes opciones de menú: 

i para iniciar
1 para opción de llamada1
2 para opción de llamada1
f para fin

Tras leer, imprimimos un mensaje, elige el mensaje que quieras. Cuando se lee un f de fin, se termina el programa. 
Si se lee algo que no corresponde con una opción de menú, se avisa al usuario que no se conoce esa opción, y se le muestra lo que 
ha introducido.

//Usa para hacerlo:
int getchar(void)
int putchar (int character);
switch
*/

#include <stdio.h>
int main()
{
    printf("Introduce una opcion: ");
    char c = getchar();
    switch (c) {
    case 'i':
        printf("Se ha iniciado el programa");
        break;
    case '1':
        printf("Se ha hecho la llamada1");
        break;
    case '2':
        printf("Se ha hecho la llamada2");
        break;
    case 'f':
        printf("Se ha finalizado el programa");
        break;
    default:
        printf("No es valido. Has introducido: ");
        putchar(c);
        break;
    }
    return 0;
}
