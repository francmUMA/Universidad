package jardines;

import java.util.concurrent.Semaphore;

public class Puerta implements Runnable {
    Contador cont;
    int numVisitantes;
    Semaphore s;

    public Puerta(Contador c, int numV, Semaphore s) {
        cont = c;
        numVisitantes = numV;
        this.s = s;
    }

    @Override
    public void run() {
        for (int i = 0; i < numVisitantes; i++) {
            try {
                s.acquire();
                cont.inc();
                s.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }

}
