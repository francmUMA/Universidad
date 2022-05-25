package interrupcion1;

public class Consumidor extends Thread {

    private RecursoCompartido recurso;

    public Consumidor(RecursoCompartido rc) {
        this.recurso = rc;
    }

    @Override
    public void run() {
        while (true) {
            try {
                recurso.extraer();
            } catch (InterruptedException e) {
            }
        }

    }

}