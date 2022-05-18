package clectoresescritoresjustocondiciones;

public class Condicion {
    public synchronized void cwait() throws InterruptedException {
        this.wait();
    }

    public synchronized void cnotify() throws InterruptedException {
        this.notify();
    }

    public synchronized void cnotifyAll() throws InterruptedException {
        this.notifyAll();
    }

}
