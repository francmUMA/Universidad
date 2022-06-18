package esqueletos;

import java.util.Random;
import java.util.concurrent.ExecutionException;

import javax.swing.SwingWorker;

public class WorkerMontecarlo extends SwingWorker<Double, Object>{

    int iteraciones;
    Panel panel;
    double montecarlo;

    public WorkerMontecarlo(int N, Panel panel){
        iteraciones = N;
        this.panel = panel;
    }

    public double aproximarPi() {
        int res = 0;
        double r = 0.5;
        double x;
        double y;
        Random random = new Random();
        for (int i = 0; i < iteraciones; i++){
            x = random.nextDouble();
            y = random.nextDouble();
            if (Math.pow((x*x + y*y), 0.5) <= 1){
                res++;
            }
        }
        return (4.0 * res) / iteraciones;
    }

    @Override
    protected Double doInBackground() throws Exception {
        return aproximarPi();
    }

    public void done(){
        try {
            panel.escribePI1(this.get());
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ExecutionException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    
}
