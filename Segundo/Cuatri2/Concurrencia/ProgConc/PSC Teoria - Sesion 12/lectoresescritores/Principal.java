package lectoresescritores;

public class Principal {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final int NE = 3;
		final int NL = 20;
		GestorBD gestor = new GestorBD();
		Thread[] esc = new Thread[NE];
		Thread[] lec = new Thread[NL];
		for (int i = 0; i < esc.length; i++) {
			esc[i] = new Thread(new Escritor(i, gestor));
		}
		for (int i = 0; i < lec.length; i++) {
			lec[i] = new Thread(new Lector(i, gestor));
		}

		for (int i = 0; i < esc.length; i++) {
			esc[i].start();
		}
		for (int i = 0; i < lec.length; i++) {
			lec[i].start();
		}
	}

}
