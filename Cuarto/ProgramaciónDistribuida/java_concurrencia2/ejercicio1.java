package java_concurrencia2;

import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class ejercicio1 {
    static List<Integer> list;

    public static class Buffer{
        private List<Integer> list;
        public Buffer(){
            list = new LinkedList<>();
        }

        public synchronized void add(){
            if (list.size() == 10) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            Random rand = new Random();
            list.add(rand.nextInt(100));
            if (list.size() == 1) notify();
        }

        public synchronized int remove(){
            if (list.size() == 0){ 
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } 
            }
            int elem = list.remove(list.size() - 1);
            if (list.size() == 9) notify();
            return elem;
        }
    }

    public static class Productor extends Thread {
        public Productor() {}

        public void run(){
            while(true){
                buffer.add();
                try {
                    sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Consumidor extends Thread {
        private int id;
        public Consumidor(int id) { this.id = id;}

        public void run(){
            while(true){
                int elem = buffer.remove();
                System.out.println(elem + " from " + id);
                try {
                    sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static Buffer buffer = new Buffer();

    public static void main(String[] args) {
        Productor p = new Productor();
        list = new LinkedList<>();
        p.start();
        Consumidor c1 = new Consumidor(1);
        Consumidor c2 = new Consumidor(2);
        
        c1.start();
        c2.start();
    }
}
