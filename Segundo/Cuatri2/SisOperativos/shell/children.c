//Muestra un listado de procesos activos en el sistema donde se muestra para cada proceso una línea con la información:
//PID, nombre del comando, número de procesos hijo y número de threads del proceso
//Dicha información se obtiene de /proc
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_name(char *line, char *name){
    int posSpace1 = 0;
    int space1found = 0;
    int posSpace2 = 0;
    int space2found = 0;
    int fin = 0;
    for (int i = 0; i < strlen(line) && !fin; i++){
        if (line[i] == ' ' && !space1found) posSpace1 = i;
        else if (line[i] == ' ' && !space2found) {
            posSpace2 = i;
            fin = 1;
        }
    }
    strncpy(name, name, strlen(name));
}

void main(){
    int pid;
    char *name;
    int numHijos;
    int numThreads;
    char *basura;
    char line[200];
    //DIR *proc = opendir("/proc");
    struct dirent *readProc;
    //while ((readProc = readdir(proc)) != NULL && (pid = atoi(readProc -> d_name)) != 0){
        //if (strcmp(readProc -> d_name, ".") != 0 && strcmp(readProc -> d_name, "..") != 0){
            //FILE *file = fopen("/proc/%s/stat", readProc -> d_name);
            FILE *file = fopen("/proc/24/stat", "r");
            if (file != NULL) {
                fgets(line,200,file);
                get_name(line, name);
                numThreads = 1;
                numHijos = 1;
                printf("%d %s %d %d\n", pid, name, numThreads, numHijos);
                fclose(file);
            }
        //}
    //}
    //closedir(proc);
}


