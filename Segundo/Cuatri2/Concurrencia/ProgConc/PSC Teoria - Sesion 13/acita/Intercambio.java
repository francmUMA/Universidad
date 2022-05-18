package acita;

/*
Primero resolver con semáforos.
Segundo resolver con wait and notify o notifyAll.
*/

public class Intercambio {
    private int v1, v2;
    private boolean hayDato1 = false;
    private boolean hayDato2 = false;

    // Acepta el dato generado por w1 y devuelve el de w2, OJO hasta que w2 no ha
    // dejado
    // dato, no se puede devolver
    public synchronized int Intercambio1(int dato) throws InterruptedException{
        v1 = dato;
        hayDato1 = true;
        while (!hayDato2)
            wait();
        notify();
        hayDato2 = false;
        return v2;
    }

    // Acepta el dato generado por w2 y devuelve el de w1, OJO hasta que w1 no ha
    // dejado
    // dato, no se puede devolver
    public synchronized int Intercambio2(int dato) throws InterruptedException{
        v2 = dato;
        hayDato2 = true;
        while (!hayDato1) 
            wait();
        notify();
        hayDato1 = false;
        return v1;
    }
}