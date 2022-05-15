package productorconsumidorbuffer;

public class Principal {
    public static void main(String[] args) {
        RecursoCompartidoBuffer rc = new RecursoCompartidoBuffer(5);
        Thread productor = new Thread(new Productor(rc));
        Thread consumidor = new Thread(new Consumidor(rc));

        productor.start();
        consumidor.start();

    }
}
