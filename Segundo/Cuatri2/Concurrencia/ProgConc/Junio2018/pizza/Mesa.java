package pizza;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Mesa {
	
	int numTrozos = 0;
	boolean pagada = false;
	boolean first = true;
	Lock l = new ReentrantLock();
	Condition estudiantes = l.newCondition();
	Condition pizzero = l.newCondition();
	Condition hacerPizza = l.newCondition();
	
	/**
	 * 
	 * @param id
	 * El estudiante id quiere una ración de pizza. 
	 * Si hay una ración la coge y sigue estudiante.
	 * Si no hay y es el primero que se da cuenta de que la mesa está vacía
	 * llama al pizzero y
	 * espera hasta que traiga una nueva pizza. Cuando el pizzero trae la pizza
	 * espera hasta que el estudiante que le ha llamado le pague.
	 * Si no hay pizza y no es el primer que se da cuenta de que la mesa está vacía
	 * espera hasta que haya un trozo para él.
	 * @throws InterruptedException 
	 * 
	 */

	public void nuevaRacion(int id) throws InterruptedException{
		l.lock();
		try {
			if (numTrozos == 0){
				if (first){
					hacerPizza.signal();
					first = false;
				}
				estudiantes.await();
			}
			if (!pagada){
				pagada = true;
				pizzero.signal();
			}
			numTrozos--;
			System.out.println("Estudiante " + id + " coge un trozo de pizza");
			if (numTrozos > 0) estudiantes.signal();
			else {
				first = true;
			}
		} finally {
			l.unlock();
		}
	}


	/**
	 * El pizzero entrega la pizza y espera hasta que le paguen para irse
	 * @throws InterruptedException 
	 */
	public void nuevaPizza() throws InterruptedException{
		l.lock();
		try {
			numTrozos = 8;
			System.out.println("Se ha entregado la pizza");
			estudiantes.signal();
			if (!pagada) pizzero.await();
			System.out.println("La pizza se ha pagado");
		} finally {
			l.unlock();
		}
	}

	/**
	 * El pizzero espera hasta que algún cliente le llama para hacer una pizza y
	 * llevársela a domicilio
	 * @throws InterruptedException 
	 */
	public void nuevoCliente() throws InterruptedException{
		l.lock();
		try {
			if (numTrozos != 0){
				hacerPizza.await();
			}
		} finally {
			l.unlock();
		}
	}

}
