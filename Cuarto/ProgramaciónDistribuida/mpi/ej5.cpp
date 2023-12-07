#include "/opt/homebrew/include/mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);                 // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // Identifica el proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Identifica el número de procesos

    /* 
     * El funcionamiento básico es el siguiente:
     * El proceso 0 es el proceso maestro y se encarga de enviar a cada proceso los datos necesarias y de recibir los resultados. Además, comprueba
     * si las matrices se pueden multiplicar.
     * Cada proceso recibe una fila de A y la matriz B completa. 
     * Cada proceso calcula su parte de la matriz C y se la envía al proceso 0.
    */

    //Creación de las matrices
    //Matriz A
    int A[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};
    //Matriz B
    int B[SIZE][SIZE] = {{1,2,3},{4,5,6},{7,8,9}};

    int rec_buffer[SIZE];

    if (rank == 0){

        //Comprobación de que las matrices se pueden multiplicar
        if (sizeof(A[0])/sizeof(A[0][0]) != sizeof(B)/sizeof(B[0][0])){
            printf("No se pueden multiplicar las matrices");
            MPI_Finalize(); // Finaliza el entorno MPI
            return 0;
        }

        //Copiar la matriz B al buffer
        int buffer[sizeof(B)][sizeof(B[0])];
        for (int i = 0; i < sizeof(B); i++){
            for (int j = 0; j < sizeof(B[0]); j++){
                buffer[i][j] = B[i][j];
            }
        }

        //Broadcast de la matriz B
        MPI_Bcast(&buffer, sizeof(buffer), MPI_INT, 0, MPI_COMM_WORLD);
        
        //Hacer un scatter de la matriz A
        MPI_Scatter(&A, SIZE, MPI_INT, rec_buffer, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

        //Calcular la parte que le toca al proceso 0
        

        //Recepción de los resultados

    } else if (rank < size){
    } 

  MPI_Finalize(); // Finaliza el entorno MPI
  return 0;
}
