#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicFUSE_lib.h"

int main() {
    struct structura_mis_datos *data = malloc(sizeof(struct structura_mis_datos));
    data -> fichero_inicial = malloc(sizeof(strlen("proverbiosycantares.txt")));
    strcpy(data -> fichero_inicial, "proverbiosycantares.txt");
    leer_fichero(data);

    int pos = buscar_fichero("/XL", data);
    printf("Titulo: %s\n", data -> nombre_ficheros[pos]);
    printf("%s\n", data -> contenido_ficheros[pos]);
}
