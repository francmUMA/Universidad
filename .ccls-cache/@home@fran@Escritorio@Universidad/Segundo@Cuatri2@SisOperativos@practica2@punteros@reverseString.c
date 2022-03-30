#include <stdio.h>
#include <string.h>

int reverse(char* fuente, char** destino){
    
}

int main(){
    char* fuente = "Esto es una cadena de prueba";
    char* destino;
    printf("Número de caracteres revertido: %d\n", reverse(fuente, &destino));
    printf("Cadena original: %s\n", fuente);
    printf("Cadena revertida: %s\n", destino);
    return 0;
}
