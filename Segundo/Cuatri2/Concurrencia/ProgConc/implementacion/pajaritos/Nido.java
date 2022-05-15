package pajaritos;

import java.util.concurrent.*;

public class Nido {
	private int B = 10; // Número máximo de bichos
	private int bichitos; // puede tener de 0 a B bichitos
	private Semaphore scBichitos = new Semaphore(1, true);
	private Semaphore hayEspacio = new Semaphore(1, true);
	private Semaphore hayBichitos = new Semaphore(0, true);

	public void come(int id) throws InterruptedException{
		hayBichitos.acquire();
		scBichitos.acquire();
		System.out.println("El bebé " + id + " ha comido un bichito. Quedan " + bichitos);
		bichitos--;
		if (bichitos > 0)
			hayBichitos.release();
		if (bichitos == B - 1)
			hayEspacio.release();
		scBichitos.release();
	}

	public void nuevoBichito(int id) throws InterruptedException{
		// el papa/mama id deja un nuevo bichito en el nido
		hayEspacio.acquire();
		scBichitos.acquire();
		System.out.println("El papá " + id + " ha añadido un bichito. Hay " + bichitos);
		bichitos++;
		if (bichitos < B)
			hayEspacio.release();
		if (bichitos == 1)
			hayBichitos.release();
		scBichitos.release();
	}
}

// CS-Bebe-i: No puede comer del nido si está vacío
// CS-Papa/Mama: No puede poner un bichito en el nido si está lleno
