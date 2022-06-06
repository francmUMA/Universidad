package mvc2;

import javax.swing.JFrame;
import java.awt.EventQueue;

public class Principal {

	public static void crearGUI() {
		JFrame ventana = new JFrame("Eventos 1");
		Vista panel = new Vista();
		NumeroThreshold modelo = new NumeroThreshold();
		Controlador ctr = new Controlador(panel, modelo);
		panel.controlador(ctr);
		ventana.setContentPane(panel);
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.pack();
		ventana.setVisible(true);
	}

	public static void main(String[] args) {

		crearGUI();

	}

}
