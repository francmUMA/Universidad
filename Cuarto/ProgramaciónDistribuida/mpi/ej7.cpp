#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);              
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    MPI_Comm_size(MPI_COMM_WORLD, &size);   

    //Creación de las matrices
    //Matriz A
    int A[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};

    //Matriz B
    int B[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};

    //Matriz C
    int C[SIZE][SIZE];
    
    //Buffer de recepción
    int rec_buffer[SIZE];
   
    //Hacer un scatter de la matriz A
    MPI_Scatter(&A, SIZE, MPI_INT, rec_buffer, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    //Cálculo de la parte de la matriz C
    int  partial_res[SIZE];
    for (int i = 0; i < SIZE; i++){
        partial_res[i] = 0;
        for (int j = 0; j < SIZE; j++){
            partial_res[i] += rec_buffer[j] * B[j][i];
        }
    }

    //Envío de la parte de la matriz C
    MPI_Gather(&partial_res, SIZE, MPI_INT, &C, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    //Mostrar la matriz C
    if (rank == 0){
        printf("Matriz C:\n");
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
