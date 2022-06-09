/**
UNIX Shell Project

Sistemas Operativos
Grados I. Informatica, Computadores & Software
Dept. Arquitectura de Computadores - UMA

Some code adapted from "Fundamentos de Sistemas Operativos", Silberschatz et al.

To compile and run the program:
   $ gcc Shell_project.c job_control.c -o Shell
   $ ./Shell          
	(then type ^D to exit program)

**/

#include "job_control.h"   // remember to compile with module job_control.c 
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE 256 /* 256 chars per line, per command, should be enough. */
job *jobList;

// -----------------------------------------------------------------------
//                            children      
// -----------------------------------------------------------------------
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

void children(){
    int pid;
    char name[20];
    int father;
    int numThreads;
    char *line = NULL;
    size_t len = 0;
    CList list;
    crearLista(&list);
    printf("PID             NAME                THREADS    CHILDS\n");
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

// -----------------------------------------------------------------------
//                            cutDir      
// -----------------------------------------------------------------------
void cutDir(char *currentDir){
    int pos = 0;
    for (int i = 0; i < strlen(currentDir); i++){
        if (currentDir[i] == '/') pos = i;
    }
    strncpy(currentDir, currentDir + (pos + 1), strlen(currentDir) - pos); 
}
    

// -----------------------------------------------------------------------
//                            manejador      
// -----------------------------------------------------------------------

void manejador(int senal){
    job *command_fin;
    int status;
    int info;
    int pid_this = 0;
    enum status status_res;

    for (int i = 1; i <= list_size(jobList); i++){
        command_fin = get_item_bypos(jobList, i);
        pid_this = waitpid(command_fin -> pgid, &status, WUNTRACED | WNOHANG | WCONTINUED);
        if (pid_this == command_fin -> pgid){
            status_res = analyze_status(status, &info);
            printf("\n \033[0;32m Background job %s with PID: %i has been %s, Info: %i \033[0;37m\n", command_fin -> command, pid_this, status_strings[status_res], info);
            if (status_res == SUSPENDED){
                command_fin -> state = STOPPED;
            } else if (status_res == EXITED || status_res == SIGNALED){ 
                command_fin -> state = EXITED;
                delete_job(jobList, command_fin);
            } else if (status_res == CONTINUED){
                command_fin -> state = BACKGROUND;
            } 
        }
    }

}


// -----------------------------------------------------------------------
//                            MAIN          
// -----------------------------------------------------------------------

int main(void)
{
	char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
	int background;             /* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2];     /* command line (of 256) has max of 128 arguments */
	// probably useful variables:
	int pid_fork, pid_wait; /* pid for created and waited process */
	int status;             /* status returned by wait */
	enum status status_res; /* status processed by analyze_status() */
	int info;				/* info processed by analyze_status() */
    jobList = new_list("jobList");
    signal(SIGCHLD, manejador);

	while (1)   /* Program terminates normally inside get_command() after ^D is typed*/
	{   
        char currentDir[256];
        ignore_terminal_signals();
        if(getcwd(currentDir, sizeof(currentDir)) == NULL){
            perror("No se ha podido obtener el nombre del directorio");
            exit(-1);
        }
		cutDir(currentDir);
        printf(" \033[1;36m🗁  %s \033[0;37m --> ", currentDir);
        fflush(stdout);     //vaciar buffer para escritura
        get_command(inputBuffer, MAX_LINE, args, &background);
        if(args[0]==NULL) continue;   // if empty command
        if (strcmp(args[0], "cd") == 0){
            int res;
            res = chdir(args[1]);
            if (res == -1 && args[1] != NULL)  printf("\033[0;31m Error: Directory not found -> %s.\033[0;37m\n", args[1]); 
        } else if (strcmp(args[0], "fg") == 0){
            int n;
            if (args[1] == NULL) n = 1;
            else { 
                n = atoi(args[1]);
                if (n == 0 || n > list_size(jobList)) {
                    printf("\033[0;31m Error: Incorrect argument -> %s.\033[0;37m\n", args[1]);
                }
            }      
            job *elem = get_item_bypos(jobList, n);
            if (elem != NULL){
                set_terminal(elem -> pgid);
                if (elem -> state == STOPPED) { 
                    killpg(elem -> pgid, SIGCONT);
                }
                elem -> state = FOREGROUND; 
                waitpid(elem -> pgid, &status, WUNTRACED);
                status_res = analyze_status(status, &info);
                set_terminal(getpid());
                printf("\033[0;32m Foreground pid: %i, command: %s, status: %s, info: %i \033[0;37m\n", elem -> pgid, elem -> command, status_strings[status_res], info);
                if (status_res == EXITED || status_res == SIGNALED) delete_job(jobList, elem);
                else if (status_res == SUSPENDED) elem -> state = STOPPED;
            }
            
        } else if (strcmp(args[0], "bg") == 0) {
            int n;
            if (args[1] == NULL) n = 1;
            else { 
                n = atoi(args[1]);
                if (n == 0 || n > list_size(jobList)) {
                    printf("\033[0;31m Error: Incorrect argument -> %s.\033[0;37m\n", args[1]);
                }
            }      
            job *elem = get_item_bypos(jobList,n);
            if (elem != NULL && elem -> state == STOPPED) {
                elem -> state = BACKGROUND;
                killpg(elem -> pgid, SIGCONT);
                printf("\033[0;32m Background job running... pid: %i, command: %s \033[0;37m \n", elem -> pgid, elem -> command);
            }
        } else if (strcmp(args[0], "jobs") == 0){
            print_job_list(jobList);
        } else if (strcmp(args[0], "children") == 0){
            children();
        } else {
            pid_fork = fork();
            if (pid_fork == 0){
                new_process_group(getpid());
                if (background == 0){
                    set_terminal(getpid());
                }
                restore_terminal_signals();
                execvp(args[0], args);
                printf("\033[0;31m Error: command not found -> %s.\033[0;37m\n", args[0]);
                exit(-1);
            } else {
                if (background == 0){
                    waitpid(pid_fork, &status, WUNTRACED);
                    set_terminal(getpid());
                    status_res = analyze_status(status, &info);
                    if (status_res == SUSPENDED){
                        job *newJob = new_job(pid_fork, args[0], STOPPED);
                        add_job(jobList, newJob);
                    }
                    printf("\033[0;32m Foreground pid: %i, command: %s, status: %s, info: %i \033[0;37m\n", pid_fork, args[0], status_strings[status_res], info);
                } else {
                    job *newJob = new_job(pid_fork, args[0], BACKGROUND);
                    add_job(jobList, newJob);                     
                    printf("\033[0;32m Background job running... pid: %i, command: %s \033[0;37m \n", pid_fork, args[0]);
                }
            }	
        }
        
	} // end while
}
