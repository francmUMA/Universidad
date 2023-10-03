package java_concurrencia2;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;

public class ejercicio1 {
    static List<Integer> list;
    static Semaphore semaforo = new Semaphore(1);

    public static class Productor extends Thread {
        public Productor() {}

        public void run(){

        }
    }

    public static void main(String[] args) {
        Productor p = new Productor();
        list = new LinkedList<>();
        p.start();
    }
}
