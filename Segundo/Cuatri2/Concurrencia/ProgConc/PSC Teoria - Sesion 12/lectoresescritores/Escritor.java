package lectoresescritores;

import java.util.Random;

public class Escritor implements Runnable {
	private static Random r = new Random();
	private GestorBD gestor;
	private int id;

	public Escritor(int id, GestorBD gestor) {
		this.id = id;
		this.gestor = gestor;
	}

	public void run() {
		while (true) {

			try {
				Thread.sleep(r.nextInt(90));// fuera de la BD
				gestor.entraEscritor(id);
				Thread.sleep(r.nextInt(100));// accediendo a la BD
				gestor.saleEscritor(id);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}
}
