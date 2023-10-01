public class Ejercicio3 {
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
        Thread t = new PiThread(100000000);
        t.start();
        try {
            t.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Pi: " + ((PiThread)t).getPi() + " Error: " + ((PiThread)t).getError());
    }
}
