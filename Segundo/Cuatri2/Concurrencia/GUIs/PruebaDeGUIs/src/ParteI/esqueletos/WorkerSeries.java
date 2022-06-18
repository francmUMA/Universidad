package ParteI.esqueletos;

import javax.swing.SwingWorker;

public class WorkerSeries {

    double iteraciones;
    // Panel panel;
    // double serie;

    public WorkerSeries(int N){
        iteraciones = Double.valueOf(N);
        // this.panel = panel;
    }

    public double aproximarPi() {
        double res = 0.0;
        int cnt = 0;
        for (double i = 1; cnt < iteraciones; i+=2.0){
            if (cnt % 2 == 0) {
                res += (4.0/i);
            } else {
                res -= (4.0/i);
            }
            cnt++;
        }
        return res;
    }

    // @Override
    // protected Void doInBackground() throws Exception {
    //     serie = aproximarPi();
    //     return null;
    // }

    // public void done(){
    //     panel.escribePI2(serie);
    // }
    
}
