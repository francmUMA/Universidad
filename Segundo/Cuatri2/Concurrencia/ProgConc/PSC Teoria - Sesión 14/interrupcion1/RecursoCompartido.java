package interrupcion1;

import java.util.concurrent.Semaphore;

//Condición Productor:
//  No puedo almacenar hasta que no se ha leido.  Un semáforo haySitio se puede encargar de sincronizar cuando hay hueco para almacenar.
//Condición Consumidor:
// No puedo extraer hasta que no se ha almacenado uno nuevo. Un semáforo hayDato se puede encargar de sincronizar cuando hay dato.

public class RecursoCompartido {
    private int recurso;
    private Semaphore haySitio = new Semaphore(1, true);

    private Semaphore hayDato = new Semaphore(0, true);

    public RecursoCompartido() {

    }

    public int extraer() throws InterruptedException {
        int datoLeido;

        hayDato.acquire();

        datoLeido = recurso;
        System.out.println("Extraído " + datoLeido);
        haySitio.release();

        return datoLeido;
    }

    public void almacenar(int r) throws InterruptedException {

        haySitio.acquire(); // 1 -> 0

        recurso = r;
        System.out.println("Almacenado " + r);

        hayDato.release(); // 0 ->1
    }

}
