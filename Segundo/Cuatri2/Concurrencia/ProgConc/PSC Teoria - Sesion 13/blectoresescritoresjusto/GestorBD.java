package blectoresescritoresjusto;

public class GestorBD {

	private int nLectores = 0;
	private boolean hayEscritor = false;
	private boolean quiereEntrarEscritor = false;
	int nEscritores = 0;

	public synchronized void entraLector(int id) throws InterruptedException {

		while (hayEscritor || quiereEntrarEscritor) {
			wait();
		}
		nLectores++;
		System.out.println("Entra lector " + id + ", hay " + nLectores + " lectores");

	}

	public synchronized void saleLector(int id) throws InterruptedException {

		nLectores--;

		System.out.println("Sale lector " + id + ", hay " + nLectores + " lectores");

		if (nLectores == 0)
			notifyAll();

	}

	public synchronized void entraEscritor(int id) throws InterruptedException {
		System.out.println("					Quiere entrar escritor.");
		quiereEntrarEscritor = true;
		nEscritores++;
		while (nLectores > 0 || hayEscritor) {
			wait();
		}
		quiereEntrarEscritor = false;
		hayEscritor = true;
		nEscritores--;
		if (nEscritores == 0) quiereEntrarEscritor = true;

		System.out.println("                    Entra escritor " + id);
	}

	public synchronized void saleEscritor(int id) throws InterruptedException {
		
		hayEscritor = false;
		System.out.println("                    Sale escritor " + id);
		notifyAll();

	}

}