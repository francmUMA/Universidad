package swingworkerdone;

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
        wm = new WorkerMontecarlo(panel.getIteraciones(), panel);
        ws = new WorkerSeries(panel.getIteraciones(), panel);
        wm.execute();
        ws.execute();
    }
    
}
