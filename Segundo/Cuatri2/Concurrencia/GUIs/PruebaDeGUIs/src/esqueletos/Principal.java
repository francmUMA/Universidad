package esqueletos;

import javax.swing.JFrame;
import java.awt.EventQueue;

public class Principal {
    public static void crearGUI(){
        JFrame frame = new JFrame("PI");
        Panel panel = new Panel();
        Controlador ctr = new Controlador(panel);
        panel.setControlador(ctr);
        frame.add(panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
			public void run() {
				crearGUI();
			}
		});
    }

}
