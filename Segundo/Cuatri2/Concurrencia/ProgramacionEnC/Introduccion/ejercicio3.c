#include <stdio.h>
#include <string.h>
int main()
{
    char cadena1[11] = "Hola mundo";
    char cadena2[15] = "Hola mundo que?";
    char cadena3[30]; 
    strcpy(cadena1, cadena2);
    printf("Cadena de tamaño %u: %s \n", (unsigned)strlen(cadena1), cadena1);
    strcat(cadena3, cadena1);
    strcat(cadena3, cadena3);
    printf("La cadena esta concatenada dos veces: %s y tiene tamaño: %u \n", cadena3, (unsigned)strlen(cadena3));

    //Comparacion de cadenas
    char cmp1[10];
    char cmp2[10];
    printf("Introduce una cadena: ");
    scanf("%s", cmp1);
    printf("Introduce otra cadena: ");
    scanf("%s", cmp2);
    if (strcmp(cmp1, cmp2) == 0){
        printf("Las cadenas son iguales");
    } else {
        printf("Las cadenas son diferentes");
    }
    printf("\n");

    //sprintf
    sprintf(cadena2, "%-10i", 5);
    printf("La cadena concatenada es: %s", cadena2);
    return 0;
}
