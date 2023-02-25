#include <stdio.h>


int main()
{
    FILE *fp;
    char data[10];
    int n;

    fp = fopen("mifichero.txt", "r");

    fread(data, sizeof(int),10, fp);
    fclose(fp);
}
