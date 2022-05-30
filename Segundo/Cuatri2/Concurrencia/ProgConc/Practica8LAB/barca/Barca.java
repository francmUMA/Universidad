package barca;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Barca extends Thread {

	private static final int C = 4;
	int numAndroid = 0;
	int numIphone = 0;
	boolean bajandose = false;
	Lock l = new ReentrantLock();
	Condition android = l.newCondition();
	Condition iphone = l.newCondition();
	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void android(int id) throws InterruptedException {
		//------------------- Locks -------------------
		l.lock();
		try  {
			while (numAndroid == C/2 && numIphone > 0 || numIphone > C/2||  numIphone + numAndroid == C || bajandose) {
				android.await();
			}
			numAndroid++;
			System.out.println("El android " + id + " se sube a la barca.");
			if (numAndroid + numIphone == C) {
				//Se inicia el viaje
				System.out.println("El viaje comienza.");
				System.out.println("Llegamos a la orilla.");
				bajandose = true;
				android.signalAll();
				iphone.signalAll();
			} else if (!bajandose) {
				android.await();
			}
			System.out.println("El android " + id + " se baja de la barca.");
			numAndroid--;
			if (numAndroid + numIphone == 0) {
				bajandose = false;
				android.signalAll();
				iphone.signalAll();
			}
		} finally {
			l.unlock();
		}

		//------------------- Monitores -------------------
		// while (numAndroid == C/2 && numIphone > 0 || numIphone > C/2||  numIphone + numAndroid == C || bajandose) {
		// 	wait();
		// }
		// numAndroid++;
		// System.out.println("El android " + id + " se sube a la barca.");
		// if (numAndroid + numIphone == C) {
		// 	//Se inicia el viaje
		// 	System.out.println("El viaje comienza.");
		// 	System.out.println("Llegamos a la orilla.");
		// 	bajandose = true;
		// 	notifyAll();
		// } else if (!bajandose) {
		// 	wait();
		// }
		// System.out.println("El android " + id + " se baja de la barca.");
		// numAndroid--;
		// if (numAndroid + numIphone == 0) {
		// 	bajandose = false;
		// 	notifyAll();
		// }
	}
	
		

	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void iphone(int id) throws InterruptedException {
		//------------------- Locks -------------------
		l.lock();
		try  {
			while (numIphone == C/2 && numAndroid > 0|| numAndroid > C/2|| numIphone + numAndroid == C || bajandose) {
				iphone.await();
			}
			System.out.println("El iphone " + id + " se sube a la barca.");
			numIphone++;
			if (numAndroid + numIphone == C) {
				//Se inicia el viaje
				System.out.println("El viaje comienza.");
				System.out.println("Llegamos a la orilla.");
				bajandose = true;
				android.signalAll();
				iphone.signalAll();
			} else if (!bajandose){
				iphone.await();
			}
			System.out.println("El iphone " + id + " se baja a la barca.");
			numIphone--;
			if (numAndroid + numIphone == 0) {
				bajandose = false;
				android.signalAll();
				iphone.signalAll();
			}
		} finally {
			l.unlock();
		}

		//------------------- Monitores -------------------
		// while (numIphone == C/2 && numAndroid > 0|| numAndroid > C/2|| numIphone + numAndroid == C || bajandose) {
		// 	wait();
		// }
		// System.out.println("El iphone " + id + " se sube a la barca.");
		// numIphone++;
		// if (numAndroid + numIphone == C) {
		// 	//Se inicia el viaje
		// 	System.out.println("El viaje comienza.");
		// 	System.out.println("Llegamos a la orilla.");
		// 	bajandose = true;
		// 	notifyAll();
		// } else if (!bajandose){
		// 	wait();
		// }
		// System.out.println("El iphone " + id + " se baja a la barca.");
		// numIphone--;
		// if (numAndroid + numIphone == 0) {
		// 	bajandose = false;
		// 	notifyAll();
		// }
	}

}

// CS-IPhone: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Android: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Todos: no pueden bajarse de la barca hasta que haya terminado el viaje