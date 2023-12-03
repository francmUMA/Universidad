#include "/opt/homebrew/include/mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identifica el proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Identifica el número de procesos

    /* El funcionamiento básico es el siguiente:
     * El proceso 0 es el proceso maestro y se encarga de enviar a cada proceso los datos necesarias y de recibir los resultados. Además, comprueba
     * si las matrices se pueden multiplicar.
     * Cada proceso recibe una fila de A y la matriz B completa. 
     * Cada proceso calcula su parte de la matriz C y se la envía al proceso 0.
    */

    //Creación de las matrices
    //Matriz A
    int A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    //Matriz B
    int B[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    if (rank == 0){
        //Comprobación de que las matrices se pueden multiplicar
        if (sizeof(A[0])/sizeof(A[0][0]) != sizeof(B)/sizeof(B[0][0])){
            printf("No se pueden multiplicar las matrices");
            MPI_Finalize(); // Finaliza el entorno MPI
            return 0;
        }
        //Envío de los datos a cada proceso
        for (int i = 1; i < size; i++){
            MPI_Send(&A[i], sizeof(A[0])/sizeof(A[0][0]), MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&B[i], sizeof(B[0])/sizeof(B[0][0]), MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        //Calcular la parte que le toca al proceso 0
        int C_0[sizeof(A[rank])];
        for (int i = 0; i < sizeof(A[rank]); i++){
            for (int k = 0; k < sizeof(B[rank]); k++){
                C_0[i] += A[rank][k] * B[k][i];
            }
        }
        //Recepción de los resultados

        } else if (rank < size){
        } 

  MPI_Finalize(); // Finaliza el entorno MPI
  return 0;
}
