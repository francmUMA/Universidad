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
		if(e.getActionCommand().equals(Vista.SI)){
			modelo.incrSi();
		} else if (e.getActionCommand().equals(Vista.NO)){
			modelo.incrNo();
		}
		vista.actualizarEtiqueta(modelo.toString());

	}

}
