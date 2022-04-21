#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistdio.h>
#include <signal.h>

int varglobal;

int main (){
    pid_t pidfork;
    varglobal = 1;
    int status;
    pidfork = fork();
    if (pidfork == 0) {
       /* execlp("ls", "ls", "-la", NULL);*/
        /*printf("No se ha ejecutado ls");*/
        /*exit(-1);*/
        int i = 0;
        printf("Hijo: pid %d: ejecutando...\n", getpid());
        while (1){
            sleep(1);
            printf("Hijo: %d s", i++);
        }
    } else {
        sleep(5);
        kill(pidfork, SIGINT);
        while (pidfork != wait(&status));
        if (WIFEXITED(status)){
            printf("Fin por exit(%d)\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)){
            printf("Fin por señal %d\n", WTERMSIG(status));
        } else {
            printf("Parado por señal %d\n", WSTOPSIG(status));
        }

    }
    exit(0);
}
