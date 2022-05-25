package mvc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Controlador implements ActionListener {

	private Vista vista;
	private NoesSies modelo;

	public Controlador(Vista panel, NoesSies modelo) {
		this.vista = panel;
		this.modelo = modelo;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}

}
