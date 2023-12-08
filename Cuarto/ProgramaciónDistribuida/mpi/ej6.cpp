#include "/opt/homebrew/include/mpi.h"
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Buffers
    int sizebuf = 26;
    char *sendbuf = (char*)malloc(sizebuf);
    strcpy(sendbuf, "Este es el string de envio");
    char *recvbuf = (char*)malloc(strlen(sendbuf)/size);

    //Mostrar cadena a enviar
    if (rank == 0){
        printf("La cadena original es: %s\n", sendbuf);
    }

    //Scatter
    MPI_Scatter(sendbuf, sizebuf, MPI_CHAR, recvbuf, strlen(sendbuf)/size, MPI_CHAR, 0, MPI_COMM_WORLD);

    //Mostrar cadena recibida
    printf("Proceso %d: %s\n", rank, recvbuf);

    /*//Revertir cadena*/
    /*char buffer;*/
    /*for (int i = 0; i < strlen(recvbuf); i++){*/
        /*buffer = recvbuf[i];*/
        /*recvbuf[i] = recvbuf[strlen(recvbuf)-i-1];*/
        /*recvbuf[strlen(recvbuf)-i-1] = buffer;*/
    /*}*/

    /*//Mostrar cadena revertida*/
    /*printf("Proceso %d: %s\n", rank, recvbuf);*/

    /*//Gather*/
    /*MPI_Gather(recvbuf, sizebuf/size, MPI_CHAR, sendbuf, strlen(sendbuf), MPI_CHAR, 0, MPI_COMM_WORLD);*/

    /*//Mostrar cadena final*/
    /*if (rank == 0){*/
        /*printf("Proceso %d: %s\n", rank, sendbuf);*/
    /*}*/

    MPI_Finalize();
    return 0;
}
