package aseos;

import java.util.concurrent.Semaphore;

public class Aseo {

	Semaphore aseo = new Semaphore(1, true);
	int numHombres = 0;
	int numMujeres = 0;
	Semaphore bloqueoHombre = new Semaphore(0, true); 
	Semaphore bloqueoMujer = new Semaphore(0, true);

	public Aseo(){}
	
	/**
	 * El hombre id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay alguna mujer en ese
	 * momento en el aseo
	 */
	public void llegaHombre(int id) throws InterruptedException{
		aseo.acquire();
		int copia = numMujeres;
		aseo.release();
		if (copia > 0)  {
			bloqueoHombre.acquire(); 
		}
		aseo.acquire();
		numHombres++;
		System.out.println("Ha entrado el hombre " + id);
		aseo.release();
	}

	/**
	 * La mujer id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay algun hombre en ese
	 * momento en el aseo
	 */
	public void llegaMujer(int id) throws InterruptedException{
		aseo.acquire();
		int copia = numHombres;
		aseo.release();
		if (copia > 0) {
			bloqueoMujer.acquire();
		}
		aseo.acquire();
		numMujeres++;
		System.out.println("Ha entrado la mujer " + id);
		aseo.release();
	}
	/**
	 * El hombre id, que estaba en el aseo, sale
	 */
	public void saleHombre(int id) throws InterruptedException{
		aseo.acquire();
		numHombres--;
		if (numHombres == 0) bloqueoMujer.release();
		System.out.println("Ha salido el hombre " + id);
		aseo.release();
	}
	
	public void saleMujer(int id) throws InterruptedException{
		aseo.acquire();
		numMujeres--;
		if (numMujeres == 0) bloqueoHombre.release();
		System.out.println("Ha salido la mujer " + id);
		aseo.release();
	}
}
