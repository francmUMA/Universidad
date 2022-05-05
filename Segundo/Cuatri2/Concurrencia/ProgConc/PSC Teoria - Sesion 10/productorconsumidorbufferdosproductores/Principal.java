package productorconsumidorbufferdosproductores;

import java.util.concurrent.Semaphore;

public class Principal {
    public static void main(String[] args) {
        Semaphore haySitio = new Semaphore(1, true);
        Semaphore hayDato = new Semaphore(0, true);
        Semaphore productores = new Semaphore(1, true);
        RecursoCompartidoBuffer rc = new RecursoCompartidoBuffer(5, haySitio, hayDato, productores);
        // 1 2 3 4 5 6 7 8
        Thread productor = new Thread(new Productor(rc, 1));

        // 10 20 30 40 50 60 70 80
        Thread productor10 = new Thread(new Productor(rc, 10));
        Thread consumidor = new Thread(new Consumidor(rc));

        productor.start();
        consumidor.start();
        productor10.start();

    }
}
