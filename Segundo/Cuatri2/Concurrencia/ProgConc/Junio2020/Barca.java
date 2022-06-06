import java.util.concurrent.Semaphore;

public class Barca {
	int numPasajeros = 0;
	int N;
	int orilla = 0;
	Semaphore mutex = new Semaphore(1, true);
	Semaphore haySitio = new Semaphore(1, true);
	Semaphore esperaCapitan = new Semaphore(0, true);
	Semaphore orilla1 = new Semaphore(0, true);
	Semaphore orilla0 = new Semaphore(1, true);
	Semaphore esperaBajada = new Semaphore(0, true);

	public Barca(int N){
		this.N = N;
	}

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public void subir(int id,int pos) throws InterruptedException{
		if (pos == 0) {
			orilla0.acquire();
		} else {
			orilla1.acquire();
		}
		haySitio.acquire();
		mutex.acquire();
		numPasajeros++;
		System.out.println("El pasajero " + id + " se ha subido a la barca en la orilla " + pos);
		if (numPasajeros < N){
			haySitio.release();
			if (orilla == 0) {
				orilla0.release();
			} else {
				orilla1.release();
			}
		} else {
			esperaCapitan.release();
		}
		mutex.release();
	}
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public int bajar(int id) throws InterruptedException{
		esperaBajada.acquire();
		mutex.acquire();
		numPasajeros--;
		System.out.println("El pasajero " + id + " ha salido de la barca en la orilla " + orilla);
		if (numPasajeros < N && numPasajeros > 0) {
			esperaBajada.release();
		} else if (numPasajeros == 0){
			haySitio.release();
		}
		mutex.release();
		return orilla;
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public void esperoSuban() throws InterruptedException{
		esperaCapitan.acquire();
		System.out.println("Comienza el viaje desde la orilla " + orilla);
	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public void finViaje() throws InterruptedException{
		mutex.acquire();
		if (orilla == 0){
			orilla1.release();
			orilla = 1; 
		} else {
			orilla0.release();
			orilla = 0;
		}
		System.out.println("Fin del viaje en la orilla " + orilla);
		mutex.release();
		esperaBajada.release();
	}

}
