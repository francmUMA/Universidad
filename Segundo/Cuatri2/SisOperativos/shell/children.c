//Muestra un listado de procesos activos en el sistema donde se muestra para cada proceso una línea con la información:
//PID, nombre del comando, número de procesos hijo y número de threads del proceso
//Dicha información se obtiene de /proc
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    int pid;
    char name[20];
    //int numHijos;
    char numThreads[2];
    char basura[20];
    char *line = NULL;
    size_t len = 0;
    printf("PID   NAME            THREADS  CHILDS\n");
    //DIR *proc = opendir("/proc");
    struct dirent *readProc;
    //while ((readProc = readdir(proc)) != NULL && (pid = atoi(readProc -> d_name)) != 0){
        //if (strcmp(readProc -> d_name, ".") != 0 && strcmp(readProc -> d_name, "..") != 0){
            //FILE *file = fopen("/proc/%s/stat", readProc -> d_name);
            FILE *file = fopen("/proc/1/status", "r");
            if (file != NULL) {
                while (getline(&line, &len, file) != -1){
                    strncpy(basura, line, 4);
                    if (strcmp("Name", basura) == 0){
                        strncpy(name, line + 6, strlen(line) - 5);
                    } else if (strcmp("Thre ", basura) == 0){
                        printf("%s", line);
                        strncpy(numThreads, line + 8, strlen(line) - 7);
                    }
                }
                printf("%d     %s           %s        %d\n", pid, name, numThreads);
                fclose(file);
            }
        //}
    //}
    //closedir(proc);
}


