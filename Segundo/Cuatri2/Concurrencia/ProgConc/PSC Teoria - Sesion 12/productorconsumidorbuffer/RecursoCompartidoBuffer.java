package productorconsumidorbuffer;

import java.util.concurrent.Semaphore;

//Condición Productor:
//  No puedo almacenar mientras el buffer no tenga sitio. 
//Condición Consumidor:
// No puedo extraer hasta que no hay datos. 
//Se necesita un índice indInsertar para conocer dónde se intertará el siguiente elemento.
//Se necesita un índice indExtraer para conocer dónde se extraerá el siguiente elemento.
//Además, el buffer va a ser tratado de forma circular, una variable tam almacenará el tamaño del buffer para actualizar correctamente los índices.

public class RecursoCompartidoBuffer {
    private int[] recurso;
    int indInsertar;
    int indExtraer;
    int tam;
    int num = 0;

    public RecursoCompartidoBuffer(int tam) {
        indInsertar = 0;
        indExtraer = 0;
        recurso = new int[tam];
        this.tam = tam;

    }

    public synchronized int extraer() throws InterruptedException{
        int datoLeido;
        while (num == 0) wait();
        datoLeido = recurso[indExtraer];
        indExtraer = (indExtraer + 1) % tam;
        num--;
        System.out.println("Extraído " + datoLeido);
        if (num == tam - 1) notify();
        return datoLeido;
    }

    public synchronized void almacenar(int r) throws InterruptedException{
        while (num == tam) wait();
        recurso[indInsertar] = r;
        indInsertar = (indInsertar + 1) % tam;
        num++;
        System.out.println("Almacenado " + r);
        if (num == 1) notify();
    }

}
