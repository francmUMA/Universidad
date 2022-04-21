package peterson03;

public class Puerta1 extends Puerta {

    public Puerta1(Peterson p, Contador c, int numV) {
        super(p, c, numV);
    }

    @Override
    public void run() {
        for (int i = 0; i < numVisitantes; i++) {
            // Sección no critica

            // Sección crítica

            // Preprotocolo
            sem.preProt1();

            // Sección no crítica
            cont.inc();

            // Postprotocolo
            sem.postProt1();

        }

    }

}
