package mvc2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Controlador implements ActionListener {

	private Vista vista;
	private NumeroThreshold modelo;
	private static Random r = new Random();

	public Controlador(Vista panel, NumeroThreshold modelo) {
		this.vista = panel;
		this.modelo = modelo;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals(Vista.calcular())) {
			try {
				modelo.establecerUmbral(vista.obtenerUmbral());
				for (int i = 0; i < vista.obtenerCantidad(); i++) {
					modelo.anyadirNumero(r.nextFloat());
				}

				List<Float> lf1 = modelo.verListaMenor();
				List<Float> lf2 = modelo.verListaMayor();

				// Imprimir 5 en línea y luego un \n
				for (int i = 0; i < lf1.size(); i++) {
					vista.anyadirListaMenores(String.format("%.02f", lf1.get(i)) + " ");
					if ((i + 1) % 5 == 0)
						vista.anyadirListaMenores("\n");
				}
				for (int i = 0; i < lf2.size(); i++) {
					vista.anyadirListaMayores(String.format("%.02f", lf2.get(i)) + " ");
					if ((i + 1) % 5 == 0)
						vista.anyadirListaMayores("\n");
				}

			} catch (NullPointerException ne) {
				JOptionPane.showMessageDialog(new JFrame(), "Se debe introducir el umbral y la cantidad", "Dialog",
						JOptionPane.ERROR_MESSAGE);
			} catch (NumberFormatException nf) {
				JOptionPane.showMessageDialog(new JFrame(), "El umbral es un número con punto y la cantidad un entero",
						"Dialog", JOptionPane.ERROR_MESSAGE);
			}

		} else if (e.getActionCommand().equals(Vista.cancelar())) {
			modelo.limpiar();
			vista.limpiar();
		}

	}

}
