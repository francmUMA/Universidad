package barrera;

import java.util.*;

public class Worker implements Runnable {

    private Barrera b;
    private int id;
    private static Random r = new Random();

    public Worker(int id, Barrera b) {
        this.b = b;
        this.id = id;
    }

    public void run() {
        while (true) {
            try {
                Thread.sleep(r.nextInt(100));
                //
                // Realizo el trabajo que tenga asignado
                //
                b.terminoIteracion(id);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }
}
