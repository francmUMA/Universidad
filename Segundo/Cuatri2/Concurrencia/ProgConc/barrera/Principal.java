package barrera;

public class Principal {
    public static void main(String[] args) {
        int N = 5;
        Barrera b = new Barrera(N);
        Thread[] w = new Thread[N];
        for (int i = 0; i < w.length; i++) {
            w[i] = new Thread(new Worker(i, b));
        }

        for (int i = 0; i < w.length; i++) {
            w[i].start();
        }
    }

}
