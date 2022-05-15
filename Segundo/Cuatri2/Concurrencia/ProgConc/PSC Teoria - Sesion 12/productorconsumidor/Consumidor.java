package productorconsumidor;

public class Consumidor implements Runnable {

    private RecursoCompartido recurso;

    public Consumidor(RecursoCompartido rc) {
        this.recurso = rc;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            try {
                recurso.extraer();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

    }

}