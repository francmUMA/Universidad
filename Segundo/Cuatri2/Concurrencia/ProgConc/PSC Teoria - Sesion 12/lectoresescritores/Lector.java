package lectoresescritores;

import java.util.*;

public class Lector implements Runnable {
	private static Random r = new Random();
	private GestorBD gestor;
	private int id;

	public Lector(int id, GestorBD gestor) {
		this.id = id;
		this.gestor = gestor;
	}

	public void run() {
		while (true) {
			try {
				Thread.sleep(r.nextInt(400));//// fuera de la BD
				gestor.entraLector(id);
				Thread.sleep(r.nextInt(100));// acceso a la BD
				gestor.saleLector(id);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}
}
