package mrusa;

import java.util.concurrent.Semaphore;

public class Coche implements Runnable {
	private int tam;
	Semaphore scNumPasajeros = new Semaphore(1, true);
	int numPasajeros = 0;
	Semaphore enMarcha = new Semaphore(0, true);
	Semaphore puedenBajarse = new Semaphore(0, true);
	Semaphore[] asientos;

	public Coche(int tam) {
		this.tam = tam;
		asientos = new Semaphore[tam];
		for (int i = 0; i < asientos.length; i++){
			asientos[i] = new Semaphore(1, true);
		}
	}

	public void subir(int id) throws InterruptedException {
		scNumPasajeros.acquire();
		int copia = numPasajeros;
		scNumPasajeros.release();
		asientos[copia].acquire();
		System.out.println("Pasajero " + id + " sube al coche");
		numPasajeros++;
		if (numPasajeros == tam) {
			enMarcha.release();
		}
		scNumPasajeros.release();
	}

	public void bajar(int id) throws InterruptedException {
		scNumPasajeros.acquire();
		numPasajeros--;

	}

	private void esperaLleno() throws InterruptedException {
		enMarcha.acquire();
		System.out.println("El tren se ha puesto en marcha");
		System.out.println("El tren ha terminado el viaje");
		puedenBajarse.release();
	}

	public void run() {
		while (true)
			try {
				this.esperaLleno();
				Thread.sleep(200);

			} catch (InterruptedException ie) {
			}

	}
}
// tam pasajeros se suben al coche->el coche da un viaje
// ->tam pasajeros se bajan del coche->......

// CS-Coche: Coche no se pone en marcha hasta que no está lleno
// CS-Pas1: Pasajero no se sube al coche hasta que no hay sitio para el.
// CS-Pas2: Pasajero no se baja del coche hasta que no ha terminado el viaje
