package fumadores;

import java.util.concurrent.*;

public class Mesa {

	// esta es una implementación pasiva para los fumadores
	// los van a despertar cuando tengan que fumar.
	private Semaphore[] fumar = {new Semaphore(0, true), new Semaphore(0, true), new Semaphore(0, true)};
	private Semaphore agente = new Semaphore(1, true); 
	private Semaphore working = new Semaphore(0, true);

	public Mesa() {

	}

	public void qFumar(int id) throws InterruptedException{
		working.acquire();
		System.out.println("Fumador " + id + " coge los ingredientes");
		fumar[id].release();
	}

	public void finFumar(int id) throws InterruptedException{
		System.out.println("Fumador " + id + " ha terminado de fumar");
		fumar[id].acquire();
		agente.release();

	}

	public void nuevosIng(int ing) throws InterruptedException{ // se pasa el ingrediente que no se pone
		agente.acquire();
		System.out.print("El agente ha puesto los ingredientes ");
		working.release();
	}

}

// CS-Fumador i: No puede fumar hasta que el fumador anterior no ha terminado
// de fumar y sus ingredientes están sobre la mesa
// CS-Agente: no puede poner nuevos ingredientes hasta que el fumador anterior
// no ha terminado de fumar
