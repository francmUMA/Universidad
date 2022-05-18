package acita;

public class Principal {

	public static void main(String[] args) {
		Intercambio inter = new Intercambio();
		Thread worker1 = new Thread(new Worker(inter, 1));
		Thread worker2 = new Thread(new Worker(inter, 2));

		worker1.start();
		worker2.start();

	}

}
// Ejemplo de salida:
/*
 * Worker id 2 envia dato 27
 * Worker id 1 envia dato 91
 * Worker id 1 recibe dato 27
 * Worker id 2 recibe dato 91
 * Worker id 1 envia dato 32
 * Worker id 2 envia dato 12
 * Worker id 2 recibe dato 32
 * Worker id 1 recibe dato 12
 */
