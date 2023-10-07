
import java.util.Random;

import java.util.concurrent.CompletionService;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorCompletionService;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ejercicio8 {
    
    public static class Data {
        private double pi;
        private double error;

        public Data(double pi, double error) {
            this.pi = pi;
            this.error = error;
        }

        public double getPi() {
            return pi;
        }

        public double getError() {
            return error;
        }
    }

    public static Data calcPi (int puntos, int id){
        int puntosDentro = 0;
        Random rand = new Random();
        double x, y;
        for (int i = 0; i < puntos; i++) {
            x = rand.nextDouble();
            y = rand.nextDouble();
            if (x * x + y * y <= 1) {
                puntosDentro++;
            }
        }
        try {
            Thread.sleep(rand.nextInt(500, 4000));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Thread " + id + " ha terminado");
        return new Data(4.0 * puntosDentro / puntos, Math.abs(Math.PI - 4.0 * puntosDentro / puntos));
    }

    public static void main(String[] args) {
        int nThreads = 10;
        ExecutorService exec = Executors.newFixedThreadPool(nThreads);
        int puntos = 1000000;
        
        CompletionService<Data> completionService = new ExecutorCompletionService<>(exec);
        for (int i = 0; i < nThreads; i++) {
            final int id = i;
            completionService.submit(() -> calcPi(puntos, id));
        }

        for (int i = 0; i < nThreads; i++) {
            try {
                Future<Data> future = completionService.take();
                Data data = future.get();
                System.out.println("Pi: " + data.getPi() + " Error: " + data.getError());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
    }
}
