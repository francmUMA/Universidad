package aseos;

import java.util.concurrent.Semaphore;

public class Aseos {
	Semaphore scClientes = new Semaphore(1, true);
	Semaphore limpiando = new Semaphore(1, true);
	Semaphore scLimpieza = new Semaphore(1, true);
	boolean vamosaLimpiar = false;
	int numClientes = 0;

	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza está
	 * trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza está trabajando
	 * o
	 * está esperando para poder limpiar los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void entroAseo(int id) throws InterruptedException {
		scClientes.acquire();
		scLimpieza.acquire();
		if (numClientes == 0 || vamosaLimpiar) {
			scLimpieza.release();
			limpiando.acquire();
		}
		
		System.out.println("El cliente " + id + " ha entrado en el baño."
				+ "Clientes en el aseo: " + numClientes);
		numClientes++;
		scClientes.release();
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void salgoAseo(int id) throws InterruptedException {
		scClientes.acquire();
		numClientes--;
		System.out.println("El cliente " + id + " ha salido del baño."
				+ "Clientes en el aseo: " + numClientes);
		
		if (numClientes == 0 && vamosaLimpiar) limpiando.release();
		scClientes.release();
	}

	/**
	 * Utilizado por el Equipo de Limpieza cuando quiere entrar en los aseos
	 * CS: El equipo de trabajo está solo en los aseos, es decir, espera hasta que
	 * no
	 * haya ningún cliente.
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void entraEquipoLimpieza() throws InterruptedException {
		System.out.println("				El equipo de limpieza quiere entrar.");
		scLimpieza.acquire();
		vamosaLimpiar = true;
		scLimpieza.release();
		limpiando.acquire();
		System.out.println("				El equipo de limpieza está trabajando.");
	}

	/**
	 * Utilizado por el Equipo de Limpieza cuando sale de los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 * 
	 */
	public void saleEquipoLimpieza() throws InterruptedException {
		scLimpieza.acquire();
		System.out.println("				El equipo de limpieza ha terminado.");
		vamosaLimpiar = false;
		scLimpieza.release();
		limpiando.release();
	}
}
