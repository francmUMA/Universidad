package productorconsumidor;

public class Productor implements Runnable {
    RecursoCompartido recurso;

    public Productor(RecursoCompartido rc) {
        recurso = rc;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            recurso.almacenar(i);
        }
    }

}
