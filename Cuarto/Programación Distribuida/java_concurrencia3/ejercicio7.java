import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class ejercicio7 {
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
        private int id;
        public Productor(int puntos, int id) {
            this.puntos = puntos;
            this.id = id;
        }

        public void run(){
            
            double x, y;
            int puntosDentro = 0;
            for (int i = 0; i < puntos; i++){
                x = Math.random();
                y = Math.random();
                if (x*x + y*y <= 1) puntosDentro++;
            }
            try {
                Random rand = new Random();
                long espera = rand.nextLong(500, 2000);
                Thread.sleep(espera);
                queue.put(new Data(puntosDentro, puntos));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            
            System.out.println("Productor " + id + " ha terminado");
            
        }
    }

    public static void main(String[] args) {
        int nThreads = 11;
        Executor exec = Executors.newFixedThreadPool(nThreads);
        exec.execute(new Consumidor());
        for (int i = 0; i < nThreads - 1; i++) {
            exec.execute(new Productor(1000000, i));
        }
    }
}
