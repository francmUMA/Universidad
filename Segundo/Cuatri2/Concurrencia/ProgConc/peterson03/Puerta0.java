package peterson03;

public class Puerta0 extends Puerta {

    public Puerta0(Peterson p, Contador c, int numV) {
        super(p, c, numV);
    }

    @Override
    public void run() {
        for (int i = 0; i < numVisitantes; i++) {
            // Sección no critica

            // Preprotocolo
            sem.preProt0();

            // Sección crítica
            cont.inc();

            // Postprotocolo
            sem.postProt0();

        }

    }

}
