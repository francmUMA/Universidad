package jardines;

import java.util.concurrent.Semaphore;

//Solventa el problema del jardín con semáforos.
//Tu solución debe funcionar para cualquier número de puertas N>1
public class Jardin {
    public static void main(String[] args) throws InterruptedException {
        Contador visitantes = new Contador();
        Semaphore s = new Semaphore(1, true);

        Thread puerta1 = new Thread(new Puerta(visitantes, 1000, s));
        Thread puerta2 = new Thread(new Puerta(visitantes, 1000, s));
        puerta2.start();
        puerta1.start();

        puerta1.join();
        puerta2.join();

        System.out.println("Hay " + visitantes.valor() + " visitantes");
    }
}