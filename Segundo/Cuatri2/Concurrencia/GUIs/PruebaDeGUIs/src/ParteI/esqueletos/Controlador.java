package ParteI.esqueletos;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Controlador implements ActionListener{

    private Panel panel;
    private WorkerMontecarlo wm;
    private WorkerSeries ws;

    public Controlador(Panel panel) {
        this.panel = panel;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        wm = new WorkerMontecarlo(panel.getIteraciones());
        ws = new WorkerSeries(panel.getIteraciones());
        double montecarlo = wm.aproximarPi();
        double serie = ws.aproximarPi();
        
        panel.escribePI1(montecarlo);
        panel.escribePI2(serie);
    }
    
}
