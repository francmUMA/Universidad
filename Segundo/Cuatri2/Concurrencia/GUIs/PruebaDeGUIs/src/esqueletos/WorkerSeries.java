package esqueletos;

import java.util.List;
import java.util.concurrent.ExecutionException;

import javax.swing.SwingWorker;

public class WorkerSeries extends SwingWorker<Double, Double>{

    double iteraciones;
    Panel panel;

    public WorkerSeries(int N, Panel panel){
        iteraciones = Double.valueOf(N);
        this.panel = panel;
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
            publish(res, (cnt / (double) iteraciones) * 100);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                
            }
        }
        publish(res, 100.0);
        return res;
    }

    @Override
    protected Double doInBackground() throws Exception {
        return aproximarPi();
    }

    public void done(){
        if (!isCancelled()){
            try {
                panel.escribePI2(this.get());
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } catch (ExecutionException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        
    }

    protected void process(List<Double> chunks){
        if (!isCancelled()){
            panel.escribePI2(chunks.get(0));
            panel.setProgresoLeibniz(chunks.get(1).intValue());
        }
    }
    
}
