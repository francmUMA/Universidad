package mvc2;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.awt.GridLayout;
import javax.swing.JTextArea;

import javax.swing.JScrollPane;

public class Vista extends JPanel {

	private JLabel etiqueta1 = new JLabel("¿Cuántos números quieres?");
	private JTextField cantidadNumeros = new JTextField(3);
	private JLabel etiqueta2 = new JLabel("¿Cuál es el umbral [0..1]?");
	private JTextField umbral = new JTextField(3);

	private JLabel mensaje = new JLabel("Ejemplo GUI PSC 2022");
	private JTextArea listaMenores = new JTextArea(10, 40);
	private JTextArea listaMayores = new JTextArea(10, 40);
	private JScrollPane scrollMenores = new JScrollPane(listaMenores);
	private JScrollPane scrollMayores = new JScrollPane(listaMayores);

	private JLabel mensaje1 = new JLabel("Area  Menores");
	private JLabel mensaje2 = new JLabel("Area  Mayores");
	private JButton btnCalcular = new JButton("Calcular");
	private JButton btnLimpiar = new JButton("Limpiar");

	private static String calcular = "calcular";
	private static String cancelar = "cancelar";

	public Vista() {
		this.setLayout(new BorderLayout());
		JPanel norte = new JPanel();
		// norte.add(etiqueta);norte.add(numero);
		norte.add(btnCalcular);
		norte.add(btnLimpiar);
		JPanel centro = new JPanel();
		centro.setLayout(new GridLayout(1, 2));
		JPanel menoresArriba = new JPanel();
		menoresArriba.add(etiqueta1);
		menoresArriba.add(cantidadNumeros);
		JPanel mayoresArriba = new JPanel();
		mayoresArriba.add(etiqueta2);
		mayoresArriba.add(umbral);

		JPanel izquierda = new JPanel();
		izquierda.setLayout(new BorderLayout());

		izquierda.add(BorderLayout.NORTH, menoresArriba);
		izquierda.add(BorderLayout.CENTER, scrollMenores);
		izquierda.add(BorderLayout.SOUTH, mensaje1);
		JPanel centro1 = new JPanel();
		centro1.setLayout(new BorderLayout());
		centro1.add(BorderLayout.NORTH, mayoresArriba);
		centro1.add(BorderLayout.CENTER, scrollMayores);
		centro1.add(BorderLayout.SOUTH, mensaje2);
		centro.add(izquierda);
		centro.add(centro1);
		this.add(BorderLayout.NORTH, norte);
		this.add(BorderLayout.CENTER, centro);
		this.add(BorderLayout.SOUTH, mensaje);
	}

	public float obtenerUmbral() throws NullPointerException, NumberFormatException {
		return Float.parseFloat(umbral.getText());
	}

	public int obtenerCantidad() throws NullPointerException, NumberFormatException {
		return Integer.parseInt(cantidadNumeros.getText());
	}

	public static String calcular() {
		return calcular;
	}

	public static String cancelar() {
		return cancelar;
	}

	public void anyadirListaMenores(String elem) {
		listaMenores.append(elem);
	}

	public void anyadirListaMayores(String elem) {
		listaMayores.append(elem);
	}

	public void controlador(ActionListener ctr) {
		btnCalcular.addActionListener(ctr);
		btnCalcular.setActionCommand(Vista.calcular);

		btnLimpiar.addActionListener(ctr);
		btnLimpiar.setActionCommand(Vista.cancelar);

	}

	public void limpiar() {
		listaMenores.setText("");
		listaMayores.setText("");
	}

}
