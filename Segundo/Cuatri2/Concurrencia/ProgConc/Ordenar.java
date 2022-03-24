import java.util.Random;

public class Ordenar {
    public static long intercambio(int[] vector, int inicio, int fin) {
        long numOperBasicas = 0;
        for (int i = inicio; i < fin - 1; i++) {
            for (int j = i + 1; j < fin; j++) {
                numOperBasicas++;
                if (vector[i] > vector[j]) {
                    int aux = vector[i];
                    vector[i] = vector[j];
                    vector[j] = aux;
                }
            }
        }
        return numOperBasicas;
    }

    public static void main(String[] args) {
        long timeA = System.currentTimeMillis();
        int[] vector = new int[40000];
        Random r = new Random(12);
        for (int i = 0; i < vector.length; i++)
            vector[i] = r.nextInt(25);
        /*
         * System.out.println("Vector desordenado");
         * for (int i = 0; i < vector.length; i++)
         * System.out.print(vector[i] + " ");
         * System.out.println();
         */

        long numOperaciones = Ordenar.intercambio(vector, 0, vector.length);
        /*
         * System.out.println("Vector ordenado");
         * for (int i = 0; i < vector.length; i++)
         * System.out.print(vector[i] + " ");
         * System.out.println();
         */

        long timeB = System.currentTimeMillis();
        System.out.println(numOperaciones + " operaciones en: " + (timeB - timeA) / 1000 + " segundos");
    }
}
