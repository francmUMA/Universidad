package clectoresescritoresjustocondiciones;

public class GestorBD {

	private int nLectores = 0;
	private boolean hayEscritor = false;
	private int nEscritores = 0;

	private Condicion okLeer = new Condicion();
	private Condicion okEscribir = new Condicion();

	public synchronized void entraLector(int id) throws InterruptedException {

		while (hayEscritor || nEscritores > 0)
			okLeer.cwait();

		nLectores++;
		System.out.println("Entra lector " + id + ", hay " + nLectores + " lectores");

	}

	public synchronized void saleLector(int id) throws InterruptedException {

		nLectores--;

		System.out.println("Sale lector " + id + ", hay " + nLectores + " lectores");

		if (nLectores == 0)
			okEscribir.cnotify();

	}

	public synchronized void entraEscritor(int id) throws InterruptedException {

		nEscritores++;
		while (nLectores > 0 || hayEscritor) {
			okEscribir.cwait();
		}

		hayEscritor = true;

		System.out.println("                    Entra escritor " + id);
	}

	public synchronized void saleEscritor(int id) throws InterruptedException {

		hayEscritor = false;
		System.out.println("                    Sale escritor " + id);
		nEscritores--;
		if (nEscritores > 0) okEscribir.cnotify();
		else okLeer.cnotifyAll();

	}

}