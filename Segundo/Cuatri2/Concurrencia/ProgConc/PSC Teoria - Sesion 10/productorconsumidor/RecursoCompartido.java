package productorconsumidor;

import java.util.concurrent.Semaphore;

//Condición Productor:
//  No puedo almacenar hasta que no se ha leido.  Un semáforo haySitio se puede encargar de sincronizar cuando hay hueco para almacenar.
//Condición Consumidor:
// No puedo extraer hasta que no se ha almacenado uno nuevo. Un semáforo hayDato se puede encargar de sincronizar cuando hay dato.

public class RecursoCompartido {
    private int recurso;
    private Semaphore hayDato;
    private Semaphore haySitio;

    public RecursoCompartido(Semaphore haySitio, Semaphore hayDato) {
        this.hayDato = hayDato;
        this.haySitio = haySitio;
    }

    public int extraer() {
        try {
            hayDato.acquire();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
        int datoLeido;
        datoLeido = recurso;
        System.out.println("Extraído " + datoLeido);
        haySitio.release();
        return datoLeido;
    }

    public void almacenar(int r) {
        try {
            haySitio.acquire();
        } catch (InterruptedException e){
            e.printStackTrace();
        }
        recurso = r;
        System.out.println("Almacenado " + r);
        hayDato.release();
    }

}
