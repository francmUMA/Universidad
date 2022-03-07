#include <stdio.h>
int main()
{
    printf("Hola, mundo");              /* funcion C de E/S */
    write(2, "Adios, mundo ", 13);      /* llamada al sistema, costosa, no buffer */
    return 0; 
}
