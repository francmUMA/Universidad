#include <stdio.h>
struct str_Libro
{
    char titulo[200];
    char autor[200];
    int paginas;
    float precio;
};

enum Meses { ENE, FEB, MAR, ABR, MAY, JUN, JUL, AGO, SEP, OCT, NOV, DIC };

struct str_Revisa_Mensual
{
    char titulo[200];
    enum Meses mes;
    float precio;
};

//struct str_item
//{
//   struct str_Libro libro;
//    struct str_Revisa_Mensual revista;
//    char tipo;
//};

union u_Item{
    struct str_Libro libro;
    struct str_Revisa_Mensual revista;
};

struct str_item{
    union u_Item item;
    char tipo;
};

const int MAX = 100;
int main()
{
    struct str_item list[MAX];
    printf("----\nTAM: %i bytes\n-----\n",sizeof(struct str_item) * MAX);
    return 0; 
}
