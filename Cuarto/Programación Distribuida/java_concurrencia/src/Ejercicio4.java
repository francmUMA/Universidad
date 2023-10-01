public class Ejercicio4 {
    public static class PiThread extends Thread{
        private int totalPoints;
        private int pointsInside;
        private double pi;
        private double error;

        public PiThread(int totalPoints){
            this.totalPoints = totalPoints;
            this.pointsInside = 0;
            pi = 0.0;
            error = 0.0;
        }

        public double getPi(){
            return pi;
        }

        public double getError(){
            return error;
        }

        @Override
        public void run() {
            double x, y;
            for(int i = 0; i < totalPoints; i++){
                x = Math.random();
                y = Math.random();
                if(x*x + y*y <= 1){
                    pointsInside++;
                }
            }
            pi = 4.0 * pointsInside / totalPoints;
            error = Math.PI - pi;
        }

    }

    public static void main(String[] args) {
        int totalPoints = 100000000;
        int numThreads = 4;
        Thread[] threads = new PiThread[numThreads];

        for(int i = 0; i < numThreads; i++){
            threads[i] = new PiThread(totalPoints/numThreads);
            threads[i].start();
        }

        for(int i = 0; i < numThreads; i++){
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        double pi = 0.0;
        double error = 0.0;

        for(int i = 0; i < numThreads; i++){
            pi += ((PiThread)threads[i]).getPi();
            error += ((PiThread)threads[i]).getError();
        }

        pi = pi / numThreads;
        error = error / numThreads;

        System.out.println("Pi: " + pi + " Error: " + error);
    }
}
