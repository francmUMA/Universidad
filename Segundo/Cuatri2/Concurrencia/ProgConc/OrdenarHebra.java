import java.util.Random;

public class OrdenarHebra {

    public static void main(String[] args) {
        long timeA = System.currentTimeMillis();
        int[] vector = new int[400000];
        Random r = new Random(12);
        for (int i = 0; i < vector.length; i++)
            vector[i] = r.nextInt(25);

        HebraO o1 = new HebraO(vector, 0, vector.length / 2);
        HebraO o2 = new HebraO(vector, vector.length / 2, vector.length);

        o1.start();

        o2.start();

        try {
            o1.join();
            o2.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }

        // espero que terminen ¡¡ IMPORTANTE !!
        OrdenarDivideVenceras.mezclar(vector, 0, vector.length / 2, vector.length);

        /*
         * System.out.println("Vector ordenado");
         * for (int i = 0; i < vector.length; i++)
         * System.out.print(vector[i] + " ");
         * System.out.println();
         */

        long timeB = System.currentTimeMillis();
        System.out.println("En paralelo: " + (timeB - timeA) / 1000 + " segundos");
    }
}
