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
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

#define MAX_LINE 256 /* 256 chars per line, per command, should be enough. */

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

	while (1)   /* Program terminates normally inside get_command() after ^D is typed*/
	{   
        char currentDir[256];
        if(getcwd(currentDir, sizeof(currentDir)) == NULL){
            perror("No se ha podido obtener el nombre del directorio");
            exit(-1);
        }
		printf(" %s --> ", currentDir);
		if(args[0]==NULL) continue;   // if empty command
        fflush(stdout);     //vaciar buffer para escritura
        get_command(inputBuffer, MAX_LINE, args, &background);
        pid_fork = fork();
        if (pid_fork == 0){
            execvp(args[0], args);
            printf("Error: command not found -> %s.\n", args[0]);
            exit(-1);
        } else {
            if (background == 0){
                waitpid(pid_fork, &status, 0);
                analyze_status(status, &info);
                printf("Foreground pid: %i, command: %s, status: %i, info: %i \n", pid_fork, args[0], status, info);
            } else {
                printf("Background job running... pid: %i, command: %s \n", pid_fork, args[0]);
            }
        }
		/* the steps are:
			 (1) fork a child process using fork()
			 (2) the child process will invoke execvp()
			 (3) if background == 0, the parent will wait, otherwise continue 
			 (4) Shell shows a status message for processed command 
			 (5) loop returns to get_commnad() function
		*/

	} // end while
}
