//Muestra un listado de procesos activos en el sistema donde se muestra para cada proceso una línea con la información:
//PID, nombre del comando, número de procesos hijo y número de threads del proceso
//Dicha información se obtiene de /proc
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

void children(){
    int pid;
    char name[20];
    char state[20];
    int father;
    int numThreads;
    char *line = NULL;
    size_t len = 0;
    printf("PID             NAME                    STATE          THREADS    PPID\n");
    DIR *proc = opendir("/proc");
    struct dirent *readProc;
    while ((readProc = readdir(proc)) != NULL){
        if (strcmp(readProc -> d_name, ".") != 0 && strcmp(readProc -> d_name, "..") != 0 && (atoi(readProc -> d_name)) != 0){
            char *path = malloc(sizeof(char) * (strlen("/proc//status") + strlen(readProc -> d_name) + 1));
            char *part1 = malloc(sizeof(char) * (strlen("/proc/") + strlen(readProc -> d_name) + 1));
            strcpy(part1, "/proc/");
            strcat(part1, readProc -> d_name);
            strcpy(path, strcat(part1,"/status"));
            FILE *file = fopen(path, "r");
            free(part1);
            free(path);
            if (file != NULL) {
                char *delim = ":";
                while (getline(&line, &len, file) != -1){
                    char *token = strtok(line, delim);
                    int who = 0;
                    for (int i = 0; i < 2; i++){
                        if (i == 0){
                            if (strcmp(token, "Name") == 0){
                                token = strtok(NULL, delim);
                                who = 1;
                            }
                            else if (strcmp(token, "Threads") == 0){
                                token = strtok(NULL, delim);
                                who = 2;
                            }
                            else if (strcmp(token, "Pid") == 0){
                                token = strtok(NULL, delim);
                                who = 3;
                            } else if (strcmp(token, "PPid") == 0){
                                token = strtok(NULL, delim);
                                who = 4;
                            } else if (strcmp(token, "State") == 0){
                                 token = strtok(NULL, delim);
                                 who = 5;
                            }
                        }
                        else {
                            if (who == 1){
                                strcpy(name, strtok(token, "\n"));
                            }
                            else if (who == 2){
                                numThreads = atoi(token);
                            }
                            else if (who == 3){
                                pid = atoi(token);
                            }
                            else if (who == 4){
                                father = atoi(token);
                            }
                            else if (who == 5){
                                strcpy(state, strtok(token, "\n"));
                            }
                        }
                    }
                }
                printf("%-8d %-20s %-15s %-10d %-6d\n", pid, name, state, numThreads, father);
                fclose(file);
            }
        }
    }
    closedir(proc);
}


