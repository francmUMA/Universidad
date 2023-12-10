#include <mpi.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char *msg = (char *) malloc(2);
    strcpy(msg, "13");

    if (rank == 0){
        char *buf = (char *) malloc(2);
        printf("Proceso %d envía el mensaje %s al proceso %d\n", rank, msg, rank + 1);
        MPI_Send(msg, 2, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(buf, 2, MPI_CHAR, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibe el mensaje %s del proceso %d\n", rank, buf, size - 1);
    } else if (rank == size - 1){
        char *buf = (char *) malloc(2);
        MPI_Recv(buf, 2, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibe el mensaje %s del proceso %d\n", rank, buf, rank - 1);
        sleep(1);
        printf("Proceso %d envía el mensaje %s al proceso %d\n", rank, msg, 0);
        MPI_Send(buf, 2, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        char *buf = (char *) malloc(2);
        MPI_Recv(buf, 2, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Proceso %d recibe el mensaje %s del proceso %d\n", rank, buf, rank - 1);
        sleep(1);
        printf("Proceso %d envía el mensaje %s al proceso %d\n", rank, msg, rank + 1);
        MPI_Send(buf, 2, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}

    
