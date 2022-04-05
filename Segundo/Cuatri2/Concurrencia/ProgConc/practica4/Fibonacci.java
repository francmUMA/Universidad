public class Fibonacci implements Runnable{

    private int fiboRes;
    private int fiboAnt;
    private int n;

    public Fibonacci(int n){
        this.n = n;    
    }

    public int getRes(){
        return fiboRes;
    }

    public int getAnt(){
        return fiboAnt;
    }

    @Override
    public void run() {
        if(n > 0){
            if (n == 1) {
                fiboAnt = 0;
                fiboRes = 1;
            } else if (n == 2){
                fiboAnt = 1;
                fiboRes = 1;
            } else {
                Fibonacci f1 = new Fibonacci(n - 1);
                Thread t1 = new Thread(f1);
                t1.start();
                // try {
                //     t1.wait();
                // } catch (InterruptedException e) {
                //     e.printStackTrace();
                // }
                try {
                    t1.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                fiboRes = f1.getRes() + f1.getAnt();
                fiboAnt = f1.getRes();
            }
        } else {
            System.out.println("Parametro erroneo.");
        }
    }

}
