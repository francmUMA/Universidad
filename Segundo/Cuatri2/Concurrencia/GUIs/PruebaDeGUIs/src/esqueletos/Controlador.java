package esqueletos;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

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
        try {
            wm.execute();
            ws.execute(); 
        } catch (NullPointerException error){
            JOptionPane.showMessageDialog(new JFrame(), "No se ha introducido ningun valor", "Dialog", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException error) {
            JOptionPane.showMessageDialog(new JFrame(), "El formato es erróneo", "Dialog", JOptionPane.ERROR_MESSAGE);
        }
        
    }
    
}
