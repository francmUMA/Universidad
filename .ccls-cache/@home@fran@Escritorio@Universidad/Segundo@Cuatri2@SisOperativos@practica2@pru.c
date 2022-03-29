#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vg;
int main(){
    int vl;
    int *p;
    vl = 5;
    p = &vl;
    printf("%p %p %p %d %d\n", &vl, &p, p, vl, *p);
    *p = 8;                 //Se cambia el valor de la variable
    printf("%p %p %p %d %d\n", &vl, &p, p, vl, *p);
    int a[5] = {1,2,3,4,5};
    int *p2;
    p2 = a;
    for (int i = 0; i < 5; i++) {
        printf("p[%d] = %d\n", i, *p2);
        p2++;               //Suma el tamaño del tipo de dato al que apunta
    }
    p2 = malloc(5*sizeof(int));
    p2[2] = 5;
    for (int i = 0; i < 5; i++){
        printf("p[%d] = %d\n", i, p2[i]);
    }
    free(p2);

    //Cadenas
    char cad[256] = "hola";
    printf("%s \n", cad);
    strcpy(cad, "adios");    
    char *p3;
    p3 = malloc(256 * sizeof(char));
    p3 = "adios";
    //para que dos punteros sean iguales deben apuntar a la misma direccion de memoria
}
