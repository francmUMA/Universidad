package parejas;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Sala {
	boolean hayHombre = false;
	boolean hayMujer = false;
	Lock l = new ReentrantLock();
	Condition hombre = l.newCondition();
	Condition mujer = l.newCondition();
	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaHombre(int id) throws InterruptedException {
		l.lock();
		try{
			while (hayHombre) {
				hombre.await();
			}
			hayHombre = true;
			while (!hayMujer) {
				System.out.println("El hombre " + id + " espera en la sala.");
				mujer.signal();
				hombre.await();
			}
			System.out.println("El hombre " + id + " ha tenido una cita.");
			Thread.sleep(1000);
			System.out.println("El hombre " + id + " sale de la sala.");
			hayHombre = false;

		} finally {
			l.unlock();
		}
	}

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaMujer(int id) throws InterruptedException {
		l.lock();
		try{
			while (hayMujer) {
				mujer.await();
			}
			hayMujer = true;
			while (!hayHombre){ 
				System.out.println("La mujer " + id + " espera en la sala.");
				hombre.signal();
				mujer.await();
			}
			System.out.println("La mujer  " + id + " ha tenido una cita.");
			Thread.sleep(1000);
			System.out.println("La mujer " + id + " sale de la sala.");
			hayMujer = false;
		} finally {
			l.unlock();
		}
			
	}
}
