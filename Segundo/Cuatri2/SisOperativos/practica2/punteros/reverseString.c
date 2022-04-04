#include <stdio.h>
#include <string.h>

int reverse(char* fuente, char** destino){
    //Guardo la direccion de memoria del primer caracter para mover el puntero hasta el final y
    //hacer que el puntero vuelva y se compare para que vuelva al inicio
    int res = 0;
    while (*fuente != '\0'){
        fuente++;
        res++;
    }
    *destino = malloc(res*sizeof(char));
    for (int i = res; i > 0; i--){
        destino[res - i] = fuente[res - i]; 
        fuente--;
    } 
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
