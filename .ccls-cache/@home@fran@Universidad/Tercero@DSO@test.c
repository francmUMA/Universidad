#include <stdio.h>


int main()
{
    FILE *fp;
    char data[10] = {0, 1,2,3,4,5,6,7,8,9};
    int n;

    fp = fopen("mifichero.txt", "r");

    for(int i = 0; i <= 10; i++){
        fprintf(fp, "%d\n", data[n]);
    }
}
