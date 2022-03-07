#include <stdio.h>
int main()
{
    float n1, n2;
    printf("Introduce un numero: ");
    scanf("%f", &n1);
    printf("Introduce otro numero: ");
    scanf("%f", &n2);
    printf("El resultado de la multiplicacion de %f y %f es %f", n1, n2, n1 * n2);
    return 0;
}
