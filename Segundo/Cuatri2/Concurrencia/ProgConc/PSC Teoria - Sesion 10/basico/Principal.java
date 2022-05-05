//https://docs.oracle.com/en/java/javase/15/docs/api/index.html
//https://docs.oracle.com/en/java/javase/15/docs/api/java.base/java/util/concurrent/Semaphore.html
//Parar antes de imprimir en el Principal, y en el run de cada hebra.
//Primero avanzar la HebraAcquire para que obtenga un permiso del semáforo.
//Tras esto avanzar la hebra Principal para que imprima la primera tanda de estados
//¿Cuantos permisos tiene el semáforo?¿En que estado está la hebra Release y la hebra Acquire?
//Continúa y avanza la HebraRelease para que haga el release.
//Avanza la hebra Principal para que imprima la segunda tanda de estados
//¿Cuantos permisos tiene el semáforo?¿En que estado está la hebra Release y la hebra Acquire?

package basico;

import java.util.concurrent.Semaphore;

public class Principal {

    public static void main(String[] args) throws InterruptedException {
        Semaphore s = new Semaphore(0, true);
        Thread hA = new Thread(new HebraAcquire(s));
        Thread hR = new Thread(new HebraRelease(s));

        hA.start();
        hR.start();

        System.out.println(s.availablePermits());
        System.out.println(hA.getState());
        System.out.println(hR.getState());

        // https://docs.oracle.com/en/java/javase/15/docs/api/java.base/java/lang/Thread.State.html
        System.out.println(s.availablePermits());
        System.out.println(hA.getState());
        System.out.println(hR.getState());

    }
}
