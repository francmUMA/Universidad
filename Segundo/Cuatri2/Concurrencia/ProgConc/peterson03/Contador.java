package peterson03;

public class Contador {
    private volatile int cont;

    public Contador() {
        cont = 0;
    }

    public void inc() {
        // No es atómico
        // load cont
        // inc 1
        // store cont
        cont++;
    }

    public int valor() {
        return cont;
    }

}
