package interrupcion0;

public class Principal {
    public static void main(String[] args) {
        Hebra h = new Hebra();
        h.start();
        try {
            Thread.sleep(1000);
            h.interrupt();
            h.join();
        } catch (InterruptedException e) {
        }
        System.out.println("Programa terminado");
    }

}
