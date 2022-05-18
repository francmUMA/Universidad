package acita;

import java.util.Random;

public class Worker implements Runnable {
    Intercambio interc;
    int id;
    private static Random r = new Random();

    public Worker(Intercambio i, int id) {
        this.id = id;
        this.interc = i;
    }

    public void run() {
        int dato;
        while (true) {
            dato = r.nextInt(100);
            try {
                Thread.sleep(100);

                if (id == 1) {
                    System.out.println("Worker id " + id + " envia dato " + dato);
                    dato = interc.Intercambio1(dato);
                    System.out.println("        Worker id " + id + " recibe dato " + dato);
                } else {
                    System.out.println("Worker id " + id + " envia dato " + dato);
                    dato = interc.Intercambio2(dato);
                    System.out.println("        Worker id " + id + " recibe dato " + dato);
                }
            } catch (InterruptedException e) {
                // TODO: handle exception
            }
        }
    }
}
