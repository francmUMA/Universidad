package ParteI.esqueletos;

import java.util.Random;

import javax.swing.SwingWorker;

public class WorkerMontecarlo{

    int iteraciones;
    //Panel panel;
    //double montecarlo;

    public WorkerMontecarlo(int N){
        iteraciones = N;
        //this.panel = panel;
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

    // @Override
    // protected Void doInBackground() throws Exception {
    //     montecarlo = aproximarPi();
    //     return null;
    // }

    // public void done(){
    //     panel.escribePI1(montecarlo);
    // }
    
}
