#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct str_Libro1
{
    char titulo[7];
    int paginas;
    int capitulos;
    char tipo;
};

struct str_Libro2
{
    char titulo[7];
    char tipo;
    int paginas;
    int capitulos;
    
};

int main()
{
    printf("char[7] %i 2*int %i char %i struct1 %i struct2 %i",7*sizeof(char),2*sizeof(int),sizeof(char),sizeof(struct str_Libro1),sizeof(struct str_Libro2));
    fflush(stdout);
    return 0;
}