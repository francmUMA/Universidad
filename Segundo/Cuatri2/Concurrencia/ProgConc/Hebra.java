
public class Hebra extends Thread {
    private int[] v;
    private int inic, fin;
    private int id;
    private boolean[] b;

    public Hebra(int[] v, int inic, int fin, boolean[] b, int id) {
        this.inic = inic;
        this.fin = fin;
        this.id = id;
        this.v = v;
        this.b = b;
    }

    public void run() {
        int i = inic;
        boolean escero = true;
        while (escero && i < fin) {
            escero = v[i] == 0;
            i++;
        }
        b[id] = escero;
    }

}
