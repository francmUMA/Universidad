package productorconsumidorbufferdosproductores;

public class Productor implements Runnable {
    RecursoCompartidoBuffer recurso;
    int factor;

    public Productor(RecursoCompartidoBuffer rc, int factor) {
        recurso = rc;
        this.factor = factor;
    }

    @Override
    public void run() {
        for (int i = 1 * factor; i < 9 * factor; i += factor) {
            recurso.almacenar(i);

        }

    }

}
