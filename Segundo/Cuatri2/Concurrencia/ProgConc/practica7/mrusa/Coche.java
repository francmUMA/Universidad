package mrusa;

import java.util.concurrent.Semaphore;

public class Coche implements Runnable {
	private int tam;
	int numPasajeros = 0;
	Semaphore scNumPasajeros = new Semaphore(1, true);
	Semaphore deViaje = new Semaphore(0, true);
	Semaphore subiendo = new Semaphore(1, true);
	Semaphore bajando = new Semaphore(0, true);
	Semaphore bajoSubo = new Semaphore(1, true);

	public Coche(int tam) {
		this.tam = tam;
	}

	public void subir(int id) throws InterruptedException {
		// id del pasajero que se sube al coche
		scNumPasajeros.acquire();
		if (numPasajeros == 0) {
			scNumPasajeros.release();
			bajoSubo.acquire();
			scNumPasajeros.acquire();
		}
		numPasajeros++;
		System.out.println("Se ha subido el pasajero " + id);
		if (numPasajeros == tam) {
			deViaje.release();
		}
		scNumPasajeros.release();
	}

	public void bajar(int id) throws InterruptedException {
		// id del pasajero que se baja del coche
		scNumPasajeros.acquire();
		if (numPasajeros == tam) {
			scNumPasajeros.release();
			bajando.release();
			bajoSubo.acquire();
			scNumPasajeros.acquire();
		} 
		numPasajeros--;
		System.out.println("Se ha bajado el pasajero " + id);
		if (numPasajeros == 0) {
			subiendo.release();
			bajoSubo.release();
		}
		scNumPasajeros.release();
	}

	private void esperaLleno() throws InterruptedException {
		// el coche espera a que este lleno para dar una vuelta
		deViaje.acquire();
		System.out.println("El viaje ha comenzado");
		System.out.println("El viaje ha finalizado");
		bajoSubo.release();
		bajando.release();
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
