/*
Existen muchos tipos de datos simples en C
https://www.cplusplus.com/doc/tutorial/variables/

El tamaño que necesita una variable a se puede consultar con la funcion sizeof(a) 
1 ¿Cuánto ocupa en tu maquina el tipo que más bytes aloja? Usa printf y sizeof para mostrar por salida el tipo y su valor.
*/

// ¿Cuánto ocupa en tu maquina el tipo que más bytes aloja? :one: 12 :two: 14 :three: 16 :four: 18
/*
Arrays:
1.- Genera y rellena un array de doubles con los valores {1.0, 2.0, 3.0, 5.0} 
*/
// ¿Has necesitado decir el tamaño del array? :one: SI :two: NO
// ¿Puedes pintar el elemento 5 con printf? :one: SI :two: NO
/*
Arrays dobles:
1.- Genera y rellena un array de doubles: double array_2d[4][4] rellénalo a mano para ser una matriz unitaria.
2.- Pinta el pantalla la matriz, usa una precisión de 2.
*/
// ¿Has necesitado decir el tamaño del array al completo? :one: SI :two: NO
// ¿Puedes pintar la fila 4 y columna 5 con printf? :one: SI :two: NO

#include <stdio.h>
int main()
{
    double array_dl[4]={1.0, 2.0, 3.0, 5.0};
    double array_2d[4][4]={{1.0, 2.0, 3.0, 5.0}, {1.0, 2.0, 3.0, 5.0}, {1.0, 2.0, 3.0, 5.0}, {1.0, 2.0, 3.0, 5.0}};
    double elem = array_dl[7];
    printf("%f",array_dl[7]);
    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%.2lf ",array_2d[i][j]);
        }
        printf("\n");
    }
    printf("%f", array_2d[4][5]); 
    return 0;
}
