import java.util.concurrent.*;

public class ejercicio4 { 
    static BlockingQueue<Integer> q;

    public static int fib(int n) {
        if (n == 0 || n == 1) return n;
        else return fib(n-1) + fib(n-2);
    }

    public static class Productor extends Thread {
        int n;
        public Productor(int n) {
            this.n = n;
        }

        public void run(){
            for (int i = 0; i < n; i++) {
                try {
                    sleep(500);
                    q.put(fib(i));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Consumidor extends Thread {
        public Consumidor() {}

        public void run(){
            while(true){
                try {
                    sleep(1000);
                    Integer fib = q.poll();
                    if (fib == null) {
                        System.out.println("No hay elementos en la cola");
                    } else {
                        System.out.println(fib);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        q = new SynchronousQueue<>();
        Thread t = new Productor(10);
        t.start();
        Thread t2 = new Consumidor();
        t2.start();
    }
}