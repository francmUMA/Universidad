package lectoresescritores;

public class GestorBD {
	private int nLectores = 0;
	private boolean hayEscritor = false;

	public synchronized void entraLector(int id) throws InterruptedException {
		while (hayEscritor) wait();
		System.out.println("Entra lector " + id + " Hay " + nLectores);
		nLectores++;
	}

	public synchronized void saleLector(int id) {
		nLectores--;
		System.out.println("Sale lector " + id + " Hay " + nLectores);
		if (nLectores == 0) notify();
	}

	public synchronized void entraEscritor(int id) throws InterruptedException {
		while(nLectores > 0 || hayEscritor) wait();
		hayEscritor = true;
		System.out.println("                    Entra escritor " + id);
	}

	public synchronized void saleEscritor(int id) {
		System.out.println("             		Sale escritor " + id);
		hayEscritor = false;
		notifyAll();
	}

}

// CS-Escritores: exclusion mutua
// CS-Lectores: puede haber varios pero nunca con un escritor