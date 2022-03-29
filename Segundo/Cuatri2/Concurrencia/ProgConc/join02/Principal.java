package join02;

import java.util.Random;

public class Principal {
    public static void main(String[] args) throws InterruptedException {
        Random r = new Random();
        int[] v;
        boolean[] b = { true, true };
        v = new int[10];
        for (int i = 0; i < v.length; i++) {
            v[i] = r.nextInt(2);
            System.out.print(v[i] + "  ");
        }
        Hebra h1 = new Hebra(v, 0, v.length / 2, b, 0);
        Hebra h2 = new Hebra(v, v.length / 2, v.length, b, 1);
        h1.start();
        h2.start();
        h1.join();
        h2.join();

        System.out.println("\nSOn todos cero " + (b[0] && b[1]));
    }

}
