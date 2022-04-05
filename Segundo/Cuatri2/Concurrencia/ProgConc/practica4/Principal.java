public class Principal {
    public static void main(String[] args) throws InterruptedException {
        int n = 21;
        Fibonacci f = new Fibonacci(n);
        Thread t = new Thread(f);
        t.start();
        t.join();
        System.out.println("El valor de fibonacci para " + n + " es " + f.getRes());
    }
}
