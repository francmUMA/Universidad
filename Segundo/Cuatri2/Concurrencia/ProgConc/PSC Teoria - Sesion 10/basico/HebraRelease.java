package basico;

import java.util.concurrent.Semaphore;

public class HebraRelease implements Runnable {
    private Semaphore s;

    public HebraRelease(Semaphore s) {
        this.s = s;
    }

    @Override
    public void run() {
        s.release();
    }

}