//DEBE COMPILARSE CON mpic++ <nombre.cpp> -o <nombre_ejecutable>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char *msg = (char *)malloc(13*sizeof(char));
    strcpy(msg, "HelloMPIWorld");
    int subsize = strlen(msg) / (size-1);


    if (rank == 0){
        //Crear subcadenas de igual tamaño para cada proceso
        for (int i = 1; i < size-1; i++){
            char *submsg = (char *)malloc(subsize*sizeof(char));
            strncpy(submsg, msg+(i-1)*subsize, subsize);
            printf("El proceso maestro envía a %d: %s\n", i, submsg);
            MPI_Send(submsg, strlen(submsg), MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        //El último proceso recibe el resto de la cadena
        char *submsg = (char *)malloc(strlen(msg) - (size-2)*subsize);
        strncpy(submsg, msg+(size-2)*subsize, strlen(msg) - (size-2)*subsize);
        printf("El proceso maestro envía a %d: %s\n", size-1, submsg);
        MPI_Send(submsg, strlen(submsg), MPI_CHAR, size-1, 0, MPI_COMM_WORLD);

        //Recibir los mensajes de los procesos
        char *res = (char *)malloc(strlen(msg)*sizeof(char));
        for (int i = 1; i < size-1; i++){
            char *submsg = (char *)malloc(subsize*sizeof(char));
            MPI_Recv(submsg, subsize, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            strncpy(res+(i-1)*subsize, submsg, subsize);
        }
        char *submsg_end = (char *)malloc((strlen(msg) - (size-2)*subsize)*sizeof(char));
        MPI_Recv(submsg_end, (strlen(msg) - (size-2)*subsize)*sizeof(char), MPI_CHAR, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        strncpy(res+(size-2)*subsize, submsg_end, strlen(msg) - (size-2)*subsize);
        printf("El proceso maestro recibe: %s\n", res);
    } else if (rank > 0 && rank < size-1){
        char *submsg = (char *)malloc(subsize*sizeof(char));
        MPI_Recv(submsg, subsize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("El proceso %d recibe: %s\n", rank, submsg);

        //Invertir la subcadena
        char buffer;
        for (int i = 0; i < strlen(submsg)/2; i++){
            buffer = submsg[i];
            submsg[i] = submsg[strlen(submsg)-i-1];
            submsg[strlen(submsg)-i-1] = buffer;
        }

        printf("El proceso %d envía: %s\n", rank, submsg);
        MPI_Send(submsg, strlen(submsg), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else if (rank == size-1){
        char *submsg = (char *)malloc((strlen(msg) - (size-2)*subsize)*sizeof(char));
        MPI_Recv(submsg, (strlen(msg) - (size-2)*subsize)*sizeof(char), MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("El proceso %d recibe: %s\n", rank, submsg);

        //Invertir la subcadena
        char buffer;
        for (int i = 0; i < strlen(submsg)/2; i++){
            buffer = submsg[i];
            submsg[i] = submsg[strlen(submsg)-i-1];
            submsg[strlen(submsg)-i-1] = buffer;
        }
        
        printf("El proceso %d envía: %s\n", rank, submsg);
        MPI_Send(submsg, strlen(submsg), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
