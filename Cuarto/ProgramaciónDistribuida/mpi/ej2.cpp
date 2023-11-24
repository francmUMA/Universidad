#include <stdio.h>
#include <mpi.h>

static int PING_PONG_LIMIT = 10;

int main(int argc, char* argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número de procesos
    int ping_pong_count = 0;
    while (ping_pong_count < PING_PONG_LIMIT) {
        if (rank == 0) {
            //Enviar bola al proceso 1
            printf("0 envía bola a 1\n");

            //Incrementar el contador de bolas
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

            //Recibir bola del proceso 1
            MPI_Recv(&ping_pong_count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("0 recibe bola de 1, Recuento: %d\n", ping_pong_count);

            
        } else if (rank == 1) {
            //Recibir bola del proceso 0
            MPI_Recv(&ping_pong_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("1 recibe bola de 0, Recuento: %d\n", ping_pong_count);
            
            //Enviar bola al proceso 0
            printf("1 envía bola a 0\n");

            //Incrementar el contador de bolas
            ping_pong_count++;

            MPI_Send(&ping_pong_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
        }
    }
    MPI_Finalize();
}
