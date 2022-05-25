package interrupcion1;

public class Principal {
    public static void main(String[] args) throws InterruptedException {
        RecursoCompartido rc = new RecursoCompartido();
        Productor productor = new Productor(rc);
        Consumidor consumidor = new Consumidor(rc);

        productor.start();
        consumidor.start();

        productor.join();
        System.out.println("Mando interruptir al consumidor");
        consumidor.interrupt();

    }
}
