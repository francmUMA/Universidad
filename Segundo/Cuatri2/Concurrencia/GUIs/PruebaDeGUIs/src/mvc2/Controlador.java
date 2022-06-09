package mvc2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Controlador implements ActionListener {

	private Vista vista;
	private NumeroThreshold modelo;
	//private static Random r = new Random();

	public Controlador(Vista panel, NumeroThreshold modelo) {
		this.vista = panel;
		this.modelo = modelo;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals(Vista.calcular())) {
			try {
				modelo.establecerUmbral(vista.obtenerUmbral());
				int N = vista.obtenerCantidad();
				CalcularNumeros calcular = new CalcularNumeros(modelo, N, vista);
				calcular.execute();

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
