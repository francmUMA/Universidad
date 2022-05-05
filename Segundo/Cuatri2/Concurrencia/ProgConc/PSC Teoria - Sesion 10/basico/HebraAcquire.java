package basico;

import java.util.concurrent.Semaphore;

public class HebraAcquire implements Runnable {
    private Semaphore s;

    public HebraAcquire(Semaphore s) {
        this.s = s;
    }

    @Override
    public void run() {
        try {
            s.acquire();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

}