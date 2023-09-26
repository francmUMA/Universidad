public class Ejercicio2 {
    public static class MyThread extends Thread{
        int id;
        public MyThread(int id){
            this.id = id;
        }

        @Override
        public void run() {
            for (int i = 0; i < 5; i++) {
                System.out.println("ID: " + id);
                try {
                    sleep(1000);
                } catch (InterruptedException ignored) {}
                System.out.println("Hebra viva: " + this.isAlive());
            }
        }
    }
    public static void main(String[] args) {
        Thread t = new MyThread(1);
        t.start();
        try {
            t.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("Hebra viva: " + t.isAlive());

        System.out.println("-------------------------------------------");

        Thread t1 = new MyThread(2);
        t1.start();
        try {
            t1.join(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("Hebra viva: " + t1.isAlive());
    }
}
