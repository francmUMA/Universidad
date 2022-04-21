package lamport;

public class Principal {
    public static void main(String[] args) {
        int N = 3;
        Panaderia pan = new Panaderia(N);
        Thread[] c = new Thread[N];
        for (int i = 0; i < N; i++) {
            c[i] = new Thread(new Cliente(i, pan));
        }
        for (int i = 0; i < N; i++) {

            c[i].start();
        }
        for (int i = 0; i < N; i++) {

            try {
                c[i].join();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        System.out.println("Clientes " + pan.contador());
    }
}