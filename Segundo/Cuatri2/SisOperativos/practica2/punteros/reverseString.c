#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int reverse(char* fuente, char** destino){
    //Guardo la direccion de memoria del primer caracter para mover el puntero hasta el final y
    //hacer que el puntero vuelva y se compare para que vuelva al inicio
    int res = strlen(fuente);
    char *aux = malloc(res * sizeof(char));
    for (int i = 0; i < res; i++){
        aux[i] = fuente[res - i - 1];
    }
    *destino = aux;
    return res;
}

int main(){
    char* fuente = "Esto es una cadena de prueba";
    char* destino;
    printf("Número de caracteres revertido: %d\n", reverse(fuente, &destino));
    printf("Cadena original: %s\n", fuente);
    printf("Cadena revertida: %s\n", destino);
    return 0;
}
