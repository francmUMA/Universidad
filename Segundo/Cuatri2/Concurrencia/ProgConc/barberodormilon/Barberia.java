package barberodormilon;

import java.util.concurrent.Semaphore;

public class Barberia {
	private int num = 0; // Numero de clientes en la sala de espera
	private Semaphore espera = new Semaphore(0, true); // Vale 0 cuando no hay clientes, 1 si tienen que esperar los
														// clientes.
														// Lo vamos a usar para dormir al barbero, cuando vale 0, se
														// debería
														// dormir. Y cuando vale 1, se debería activar.
	private Semaphore scNum = new Semaphore(1, true); // lo usamos para gestionar la sección crítica en el acceso a num
	private boolean primer = true; // Para gestionar el comportamiento del barbero la primera vez que se entra en
									// su método

	public void llegaCliente() throws InterruptedException {
		scNum.acquire();
		num++;
		System.out.println("Llega cliente " + num);
		if (num == 1){
			espera.release();
		}
		scNum.release();
	}

	public void pelaCliente() throws InterruptedException {
		if (primer) {
			espera.acquire();
			primer = false;
		} 
		scNum.acquire();
		// la primera vez que entramos, intentamos obt
		num--;
		System.out.println("Pelo cliente " + num);
		// if (num == 0){
		// 	primer = true;
		// }
		int copia = num;
		scNum.release();
		if (copia == 0){
			espera.acquire();
		} 
		
	}
}
