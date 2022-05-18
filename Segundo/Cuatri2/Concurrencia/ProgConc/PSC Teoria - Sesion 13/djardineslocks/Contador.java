package djardineslocks;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Contador {
    private int cont;
    private Lock l = new ReentrantLock();

    public Contador() {
        cont = 0;
    }

    public synchronized void inc() {
        l.lock();
        try{
            cont++;
        } finally{
            l.unlock();
        }
    }

    public synchronized int valor() {
        return cont;
    }

}
