package productorconsumidorbuffer;

import java.util.concurrent.Semaphore;

public class Principal {
    public static void main(String[] args) {
        Semaphore haySitio = new Semaphore(1, true);
        Semaphore hayDato = new Semaphore(0, true);
        RecursoCompartidoBuffer rc = new RecursoCompartidoBuffer(5, haySitio, hayDato);
        Thread productor = new Thread(new Productor(rc));
        Thread consumidor = new Thread(new Consumidor(rc));

        productor.start();
        consumidor.start();

    }
}
