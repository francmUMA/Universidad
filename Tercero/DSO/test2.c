#include <stdio.h>


int main()
{
    FILE *fp;
    char data[10];
    int n;

    fp = fopen("mifichero.txt", "r");

    for(int i = 0; i <= 10; i++){
        fscanf(fp,"%d\n",data[n]);
        printf(fp, "%d\n", data[n]);
    }
}
