package productorconsumidor;

public class Principal {
    public static void main(String[] args) {
        RecursoCompartido rc = new RecursoCompartido();
        Thread productor = new Thread(new Productor(rc));
        Thread consumidor = new Thread(new Consumidor(rc));

        productor.start();
        consumidor.start();

    }
}
