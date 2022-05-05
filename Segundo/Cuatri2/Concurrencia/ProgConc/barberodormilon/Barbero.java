package barberodormilon;

import java.util.Random;

public class Barbero implements Runnable {
	private Random r = new Random();
	private Barberia b;

	public Barbero(Barberia b) {
		this.b = b;
	}

	public void run() {
		while (true) {
			try {
				b.pelaCliente();
				Thread.sleep(r.nextInt(200));
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
