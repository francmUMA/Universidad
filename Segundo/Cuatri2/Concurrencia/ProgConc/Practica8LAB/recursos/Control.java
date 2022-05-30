package recursos;

import java.util.ArrayDeque;
import java.util.Queue;

public class Control {
	private int NUM;// numero total de recursos
	private int numRec;
	Queue<Integer> espera = new ArrayDeque<>();

	public Control(int num) {
		this.NUM = num;
		this.numRec = num;
	}

	public synchronized void qRecursos(int id, int num) throws InterruptedException {
		if(!espera.contains(id)){
			System.out.println("Proceso con id: " + id + " ha entrado en la cola");
			espera.add(id);
		}
		while (!espera.isEmpty() && espera.peek() != id){
			wait();
		}
		System.out.println("Proceso " + id + " pide " + num + " recursos. Quedan: " + numRec);
		while(numRec < num){
			wait();
		}
		numRec -= num;
		System.out.println("El proceso " + id + " ha cogido " + num + " recursos. Quedan: " + numRec);
		espera.poll();
		System.out.println("El proceso " + id + " ha salido de la cola");
		notifyAll();
	}

	public synchronized void libRecursos(int id, int num) {
		numRec = numRec + num;
		System.out.println("El proceso " + id + " ha liberado " + num + " recursos. Recursos totales: " + numRec);
		notifyAll();
	}
}
// CS-1: un proceso tiene que esperar su turno para coger los recursos
// CS-2: cuando es su turno el proceso debe esperar hasta haya recursos
// suficiente
// para él
