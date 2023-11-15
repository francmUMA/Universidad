import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class ejercicio6 {
    public static class Data {
        private int puntosDentro;
        private int puntosTotales;

        public Data(int puntosDentro, int puntosTotales) {
            this.puntosDentro = puntosDentro;
            this.puntosTotales = puntosTotales;
        }

        public int getPuntosDentro() {
            return puntosDentro;
        }

        public int getPuntosTotales() {
            return puntosTotales;
        }
    }

    static BlockingQueue<Data> queue = new LinkedBlockingQueue<>(10);

    public static class Consumidor implements Runnable{
        private int puntosDentro;
        private int puntosTotales;
        public Consumidor() {}

        public void run(){
            while(true){
                try {
                    Data data = queue.take();
                    puntosDentro += data.getPuntosDentro();
                    puntosTotales += data.getPuntosTotales();
                    System.out.println("Puntos dentro: " + puntosDentro + " Puntos totales: " + puntosTotales);
                    System.out.println("Pi: " + (4.0 * puntosDentro / puntosTotales) + " Error: " + (Math.PI - (4.0 * puntosDentro / puntosTotales)));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static class Productor implements Runnable{
        private int puntos;
        public Productor(int puntos) {
            this.puntos = puntos;
        }

        public void run(){
            while(true){
                double x, y;
                int puntosDentro = 0;
                for (int i = 0; i < puntos; i++){
                    x = Math.random();
                    y = Math.random();
                    if (x*x + y*y <= 1) puntosDentro++;
                }
                try {
                    queue.put(new Data(puntosDentro, puntos));
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        int nThreads = 11;
        Executor exec = Executors.newFixedThreadPool(nThreads);
        exec.execute(new Consumidor());
        for (int i = 0; i < nThreads - 1; i++) {
            exec.execute(new Productor(1000000));
        }
    }
}
