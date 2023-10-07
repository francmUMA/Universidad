public class Ejercicio5 {

    public static class WriterThread extends Thread{
        private String message;

        public WriterThread(String message){
            this.message = message;
        }

        @Override
        public void run() {
            for(int i = 0; i < 5; i++){
                synchronized(lock){
                    System.out.print(message);
                    lock.notify();
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    private static Object lock = new Object();

    public static void main(String[] args) {
        Thread t1 = new WriterThread("Hola ");
        Thread t2 = new WriterThread(" Mundo\n");
        t1.start();
        t2.start();
    }

}
