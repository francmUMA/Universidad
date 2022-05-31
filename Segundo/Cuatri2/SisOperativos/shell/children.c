//Muestra un listado de procesos activos en el sistema donde se muestra para cada proceso una línea con la información:
//PID, nombre del comando, número de procesos hijo y número de threads del proceso
//Dicha información se obtiene de /proc
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_name(char *name){
    //elimina el primer '(' y la primera '/' del array de char pasado por parámetro
    char res[strlen(name) - 3];
    for(int i = 1; name[i] != '/' && name[i] != ')'; i++){
        res[i-1] = name[i];
    }
    strcpy(name, res);
}

void main(){
    int pid;
    char *name;
    int numHijos;
    int numThreads;
    char *basura;
    char line[200];
    printf("PID   NAME            THREADS  CHILDS\n");
    //DIR *proc = opendir("/proc");
    struct dirent *readProc;
    //while ((readProc = readdir(proc)) != NULL && (pid = atoi(readProc -> d_name)) != 0){
        //if (strcmp(readProc -> d_name, ".") != 0 && strcmp(readProc -> d_name, "..") != 0){
            //FILE *file = fopen("/proc/%s/stat", readProc -> d_name);
            FILE *file = fopen("/proc/1/stat", "r");
            if (file != NULL) {
                fscanf(file, "%d %s", &pid, name);
                get_name(name);
                numThreads = 1;
                numHijos = 1;
                printf("%d     %s           %d        %d\n", pid, name, numThreads, numHijos);
                fclose(file);
            }
        //}
    //}
    //closedir(proc);
}


