// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Ejercicio1 {
    public static class MiThread extends Thread {
        private int id;
        public MiThread(int id){
            this.id = id;
        }
        public void run(){
            System.out.println("ID: " + id);
        }
    }

    public static class MiRunnable implements Runnable{
        int id;
        public MiRunnable(int id){
            this.id = id;
        }

        @Override
        public void run() {
            System.out.println("ID: " + id);
        }
    }

    public static void main(String[] args) {
        Thread t1 = new MiThread(1);
        t1.start();

        MiRunnable m = new MiRunnable(2);
        Thread t2 = new Thread(m);
        t2.start();
    }
}