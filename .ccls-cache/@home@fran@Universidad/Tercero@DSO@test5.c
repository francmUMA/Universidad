#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <strings.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int no;
    char data[10] = {10,11,12,13,14,15,16,17,18,19};
    int *p;
    int tam = sizeof(int) * 10;


    no = open("mifichero.txt",O_CREAT|O_RDWR, 0664);

    ftruncate(no, tam + 1);
    p=mmap(NULL, tam, PROT_READ|PROT_WRITE, MAP_SHARED, no, 0);
    if (!p){
        printf("ERRORRRRRRRRR\n");
    } 
    
    bcopy(data, p, tam);

    close(no);
}
