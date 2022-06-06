import java.util.ArrayDeque;
import java.util.Queue;

public class BarcaML {

	int N;
    Queue<Integer> clientesOrilla0 = new ArrayDeque<>();
    Queue<Integer> clientesOrilla1 = new ArrayDeque<>();
    int numPasajeros = 0;
    int orilla = 0;
    boolean subida = true;
    boolean viaje = false;

	public BarcaML(int N){
		this.N = N;
	}

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public synchronized void subir(int id,int pos) throws InterruptedException{
        if (pos == 0){
            clientesOrilla0.add(id);
            while (!subida || pos != orilla ||  clientesOrilla0.peek() != id) {
                wait();
            }
        } else if (pos == 1){
            clientesOrilla1.add(id);
            while (!subida || pos != orilla || clientesOrilla1.peek() != id) {
                wait();
            }
        }
        
        if (pos == 0){
            clientesOrilla0.poll();
        } else {
            clientesOrilla1.poll();
        }
        numPasajeros++;
        System.out.println("El pasajero " + id + " se ha subido a la barca en la orilla " + pos);
        if (numPasajeros == N) {
            viaje = true;
            subida = false;
        }
        notifyAll(); 
	}
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public synchronized int bajar(int id) throws InterruptedException{
		while (viaje || subida) {
            wait();
        }
        numPasajeros--;
        System.out.println("El pasajero " + id + " ha salido de la barca en la orilla " + orilla);
        if (numPasajeros == 0) {
            subida = true;
            notifyAll();
        }
        return orilla;
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public synchronized void esperoSuban() throws InterruptedException{
		while (!viaje) {
            wait();
        }
        System.out.println("El capitan ha comenzado el viaje en la orilla " + orilla);
	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public synchronized void finViaje() throws InterruptedException{
		System.out.println("El capitan ha terminado el viaje en la orilla " + orilla);
        if (orilla == 0){
            orilla = 1;
        } else {
            orilla = 0;
        }
        viaje = false;
        notifyAll();
	}

}

