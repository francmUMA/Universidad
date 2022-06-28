#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {
    FILE *f = fopen("prueba.bin", "wb");
    char cadena[50] = "He escrito esto en binario";
    fwrite(cadena, sizeof(char), 50, f);
    fclose(f);

    //Leer la cadena escrita en binario
    f = fopen("prueba.bin", "rb");
    char cadena2[50];
    fread(cadena2, sizeof(char), 50, f);   
    printf("%s y tiene tamanyo: %u\n", cadena2, sizeof(cadena2));
    fclose(f);

    //Concatenar una cadena nueva a la cadena leida
    f = fopen("prueba.bin", "ab");
    fwrite("\nEsta es una cadena concatenada", sizeof(char), 40, f);
    fclose(f);

    //Leer la cadena concatenada
    f = fopen("prueba.bin", "rb");
    while (fread(cadena2, sizeof(char), 50, f) != 0) {
        printf("%s y tiene tamanyo %u", cadena2, sizeof(cadena2));
    }
    fclose(f);

    //Escribir una cadena en un fichero de texto normal
    f = fopen("prueba.txt", "w");
    fprintf(f, "Esta es una cadena escrita en un fichero de texto normal");
    fclose(f);

    //Leer la cadena escrita en un fichero de texto normal
    //Con la funcion fscanf se lee un formato concreto
    f = fopen("prueba.txt", "r");
    char cadena3[100];
    fgets(cadena3, 100, f);
    printf("\n%s", cadena3);
    fclose(f);

}
