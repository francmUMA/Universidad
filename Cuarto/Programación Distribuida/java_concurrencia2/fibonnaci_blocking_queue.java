import java.util.concurrent.*;

public class fibonnaci_blocking_queue { 
    static BlockingQueue<Integer> q;
    public static class Productor extends Thread {
        int n;
        int res;
        public Productor(int n) {
            this.n = n;
            this.res = 0;
        }    

        public int getRes(){
            return res;
        }

        public void run(){
            if (n == 0 || n == 1){
                try {
                    q.put(1);
                    res = 1;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else  {
                Thread t_n1 = new Productor(n-1);
                Thread t_n2 = new Productor(n-2);
                t_n1.start();
                t_n2.start();
                try {
                    t_n1.join();
                    t_n2.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                res = ((Productor)t_n1).getRes() + ((Productor)t_n2).getRes();
                try {
                    q.put(res);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public class Consumidor extends Thread {
        int n;
        public Consumidor(int n) {
            this.n = n;
        }

        public void run(){
            for (int i = 0; i < n; i++) {
                try {
                    System.out.println(q.take());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        q = new LinkedBlockingQueue<>(10);
        Thread t = new Productor(10);
        t.start();
        Thread t2 = new Consumidor();
        t2.start();
    }
}