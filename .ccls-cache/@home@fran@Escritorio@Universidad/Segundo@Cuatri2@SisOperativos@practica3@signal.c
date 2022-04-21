#include <stdio.h>
#include <signal.h>

void manejador(int senal){
    static int n = 0;
    printf(" Se ha recibido la señal #%d (2=SIGINT=Ctrl + C) %d/3\n", senal, ++n);
    if (n == 3){
        printf("Reestableciendo comportamiento por defecto...\n");
        signal(SIGINT, SIG_DFL);
    }
}

int main(){
    signal(SIGINT, manejador);
    while (1);
}
