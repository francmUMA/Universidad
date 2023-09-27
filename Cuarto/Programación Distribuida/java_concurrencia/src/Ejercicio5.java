public class Ejercicio5 {
    public static class WriterThread extends Thread {
        String text;
        int id;

        public WriterThread(String text, int id){
            this.text = text;
            this.id = id;
        }

        @Override
        public void run() {
            for (int i = 0; i < 5; i++) {
                if (turno && id == 1){
                    System.out.print(text);
                    turno = false;
                    notifyAll();
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                } else if(!turno &&  id == 2) {
                    System.out.print(text);
                    turno = true;
                    notifyAll();
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }
    static boolean turno = true;

    public static void main(String[] args) {
        Thread t_hola = new WriterThread("Hola", 1);
        Thread t_mundo = new WriterThread(" Mundo\n", 2);
        t_hola.start();
        t_mundo.start();
    }
}
