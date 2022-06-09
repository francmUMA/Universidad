//Muestra un listado de procesos activos en el sistema donde se muestra para cada proceso una línea con la información:
//PID, nombre del comando, número de procesos hijo y número de threads del proceso
//Dicha información se obtiene de /proc
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

typedef struct childrenJob *CList;

struct childrenJob {
    int pid;
    char command[20];
    int n_children;
    int n_threads;
    int ppid;
    CList next;
};

void crearLista(CList *lista){
    *lista = NULL;
}

void add_children(CList *lista, int pid, char *name, int nThreads, int father){
    CList newJob = malloc(sizeof(struct childrenJob));
    if (newJob == NULL){
        printf("No se ha podido pedir memoria");
        exit(-1);
    }
    newJob -> pid = pid;
    strcpy(newJob -> command, name);
    newJob -> n_children = 0;
    newJob -> n_threads = nThreads;
    newJob -> ppid = father;
    newJob -> next = NULL;
    if (*lista == NULL){
        (*lista) = newJob;
    } else {
        CList ptr = (*lista);
        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = newJob;
    }
}



void main(){
    int pid;
    char name[20];
    int father;
    int numThreads;
    char *line = NULL;
    size_t len = 0;
    CList list;
    crearLista(&list);
    printf("PID         NAME                THREADS    CHILDS\n");
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
                        }
                    }
                }
                add_children(&list, pid, name, numThreads, father);
                fclose(file);
            }
        }
    }
    closedir(proc);

    //Actualizar el atributo n_children de cada proceso
    CList ptr = list;
    while (ptr != NULL){
        CList ptr2 = list;
        while (ptr2 != NULL){
            if (ptr -> pid == ptr2 -> ppid){
                ptr -> n_children++;
            }
            ptr2 = ptr2 -> next;
        }
        ptr = ptr -> next;
    }

    //Mostrar el listado
    ptr = list;
    while (ptr != NULL){
        printf("%-8d %-20s %-10d %-6d\n", ptr -> pid, ptr -> command, ptr -> n_threads, ptr -> n_children);
        ptr = ptr -> next;
    }
}


