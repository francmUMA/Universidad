package jardines;

public class Contador {
    private volatile int cont;

    public Contador() {
        cont = 0;
    }

    public void inc() {
        cont++;
    }

    public int valor() {
        return cont;
    }

}
