package Jardin;

public class Puerta implements Runnable{

    Contador c;
    int numVisitantes;

    public Puerta(Contador c, int numV){
        this.c = c;
        this.numVisitantes = numV;
    }

    @Override
    public void run() {
        for (int i = 0; i < numVisitantes; i++){
            c.inc();
        }
    }
    
}
