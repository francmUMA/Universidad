package mvc;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Vista extends JPanel {
	private JButton bSi = new JButton("sí");
	private JButton bNo = new JButton("no");
	private JLabel ms = new JLabel("¿Es verdad?");
	static String SI = "SI";
	static String NO = "NO";

	public Vista() {
		this.setLayout(new BorderLayout());
		JPanel pnorte1 = new JPanel();
		pnorte1.add(bSi);
		pnorte1.add(bNo);
		this.add(pnorte1, BorderLayout.NORTH);
		this.add(ms, BorderLayout.SOUTH);
	}

	public void actualizarEtiqueta(String m) {
		ms.setText(m);
	}

}
