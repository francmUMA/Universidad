#include "/opt/homebrew/include/mpi.h"
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if (rank == 0){
        char *msg = (char*)malloc(13);
        strcpy(msg, "HelloMPIWorld");
    
        //Envir a cada proceso un trozo de la cadena
        char *submsg = (char*)malloc(13 / size + 1);
        printf("Size msg: %lu, Size submsg: %lu\n", sizeof(msg),sizeof(msg) / size + 1);
        for (int i = 1; i < size; i++){
            //Crear subcadena
            strcpy(submsg, "");
            for (int j = (i-1)*(sizeof(msg)/size); j < (sizeof(msg) / size) * i; j++){
                printf("j: %d, m[j]: %c\n", j, msg[j]);
                strcat(submsg, &msg[j]); 
            }
            printf("Proceso %d: %s\n", i, submsg);
            //MPI_Send(submsg, sizeof(submsg), MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }}
/*    } else {*/
        /*char * msg = (char*)malloc(sizeof(msg) / size + 1);*/
        /*MPI_Recv(&msg, 13, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);*/
        /*printf("Proceso %d: %s\n", rank, msg);*/
    /*}*/
    MPI_Finalize();
}
