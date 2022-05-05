package productorconsumidorbuffer;

public class Consumidor implements Runnable {

    private RecursoCompartidoBuffer recurso;

    public Consumidor(RecursoCompartidoBuffer rc) {
        this.recurso = rc;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            recurso.extraer();
        }

    }

}