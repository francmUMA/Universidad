package productorconsumidor;

//Condición Productor:
//  No puedo almacenar hasta que no se ha leido.  
//Condición Consumidor:
// No puedo extraer hasta que no se ha almacenado uno nuevo. 
public class RecursoCompartido {
    private int recurso;
    private boolean almacenado = false;

    public RecursoCompartido() {
    }

    public synchronized int extraer() throws InterruptedException{
        while (!almacenado){
            wait();
        }
        almacenado = false;
        System.out.println("Extraído " + recurso);
        notify();
        return recurso;
    }

    public synchronized void almacenar(int r) throws InterruptedException{
        while (almacenado) wait();
        almacenado = true;
        recurso = r;
        notify();
        System.out.println("Almacenado " + r);
    }

}
