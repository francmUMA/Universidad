package peterson03;

public class Puerta implements Runnable {
    Contador cont;
    int numVisitantes;
    Peterson sem;

    public Puerta(Peterson p, Contador c, int numV) {
        cont = c;
        numVisitantes = numV;
        sem = p;
    }

    @Override
    public void run() {
        for (int i = 0; i < numVisitantes; i++) {
            // Sección no critica
            // Preprotoclo
            // Sección crítica
            // Postprotocolo
            // Sección no crítica
            cont.inc();
        }

    }

}
