import java.util.Random;

public class OrdenarDivideVenceras {
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

    public static long mezclar(int[] v, int inic, int m, int fin) {
        int i = inic;
        int j = m;
        long numOperBasicas = 0;
        int cont = 0;
        int w[] = new int[v.length];
        w = v;

        while ((i < m) && (j < fin)) {
            if (w[i] <= w[j]) {
                v[cont] = w[i];
                i++;
            } else {
                v[cont] = w[j];
                j++;
            }
            cont++;
        }
        while (i < m) {
            v[cont] = w[i];
            i++;
            cont++;
            numOperBasicas++;
        }
        while (j < fin) {
            v[cont] = w[j];
            j++;
            cont++;
            numOperBasicas++;
        }
        return numOperBasicas;
    }

    public static void main(String[] args) {
        long timeA = System.currentTimeMillis();
        int[] vector = new int[400000];
        Random r = new Random(12);
        for (int i = 0; i < vector.length; i++)
            vector[i] = r.nextInt(25);
        /*
         * System.out.println("Vector desordenado");
         * for (int i = 0; i < vector.length; i++)
         * System.out.print(vector[i] + " ");
         * System.out.println();
         */

        long numOperaciones1 = OrdenarDivideVenceras.intercambio(vector, 0, vector.length / 2);
        long numOperaciones2 = OrdenarDivideVenceras.intercambio(vector, vector.length / 2, vector.length);
        long numOperaciones3 = OrdenarDivideVenceras.mezclar(vector, 0, vector.length / 2, vector.length);

        /*
         * System.out.println("Vector ordenado");
         * for (int i = 0; i < vector.length; i++)
         * System.out.print(vector[i] + " ");
         * System.out.println();
         */

        long timeB = System.currentTimeMillis();
        System.out.println(numOperaciones1 + numOperaciones2 + numOperaciones3 + " operaciones en: "
                + (timeB - timeA) / 1000 + " segundos");
    }
}