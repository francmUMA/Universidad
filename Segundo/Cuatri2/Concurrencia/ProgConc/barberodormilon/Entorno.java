package barberodormilon;

import java.util.*;

public class Entorno implements Runnable {
	private Random r = new Random();
	private Barberia b;

	public Entorno(Barberia b) {
		this.b = b;
	}

	public void run() {
		while (true) {
			try {
				Thread.sleep(r.nextInt(200));
				b.llegaCliente();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
