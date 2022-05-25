package electoresescritoresjustolocks;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class GestorBD {

	private int nLectores = 0;
	private boolean hayEscritor = false;
	private int nEscritores = 0;

	private Lock l = new ReentrantLock();

	private Condition okLeer = l.newCondition();
	private Condition okEscribir = l.newCondition();

	public void entraLector(int id) throws InterruptedException {
		l.lock();
		try{
			while (hayEscritor || nEscritores > 0)
				okLeer.await();

			nLectores++;
			System.out.println("Entra lector " + id + ", hay " + nLectores + " lectores");
		} finally {
			l.unlock();
		}
	}

	public void saleLector(int id) throws InterruptedException {
		l.lock();
		try{
			nLectores--;

			System.out.println("Sale lector " + id + ", hay " + nLectores + " lectores");

			if (nLectores == 0)
				okEscribir.signalAll();
		} finally{
			l.unlock();
		}
	}

	public void entraEscritor(int id) throws InterruptedException {
		l.lock();
		try {
			nEscritores++;
			while (nLectores > 0 || hayEscritor) {
				okEscribir.await();
			}

			hayEscritor = true;

			System.out.println("                    Entra escritor " + id);
		} finally {
			l.unlock();
		}
	}

	public synchronized void saleEscritor(int id) throws InterruptedException {
		l.lock();
		try{
			hayEscritor = false;
			System.out.println("                    Sale escritor " + id);
			nEscritores--;
			if (nEscritores > 0) okEscribir.signal();
			else okLeer.signalAll();
		} finally {
			l.unlock();
		}
	}

}