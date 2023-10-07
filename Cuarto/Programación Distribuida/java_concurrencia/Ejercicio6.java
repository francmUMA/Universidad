import java.util.Map;
import java.util.concurrent.Semaphore;
import java.util.HashMap;

public class Ejercicio6 {

    public static class AnalizerThread extends Thread{
        private String frase;
        private int inicio;
        private int fin;

        public AnalizerThread(String frase, int inicio, int fin){
            this.frase = frase;
            this.inicio = inicio;
            this.fin = fin;
        }

        public void run(){
            for (int i = inicio; i < fin; i++) {
                char c = frase.charAt(i);
                try {
                    mutex.acquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if (data.containsKey(c)) {
                    data.put(c, data.get(c) + 1);
                } else {
                    data.put(c, 1);
                }
                mutex.release();
            }
        }

    }

    static Map<Character, Integer> data = new HashMap<Character, Integer>();
    static Semaphore mutex = new Semaphore(1);
    public static void main(String[] args) {
        String frase = "Une equivalente de los dictionarios en Python en Java," + 
        "sería un HashMap en donde también puedes almacenar elementos definidos" + 
        "por llave (key) y valor (value).";
        
        int numThreads = 5;
        int size = frase.length() / numThreads;

        Thread[] threads = new AnalizerThread[numThreads];

        for (int i = 0; i < numThreads; i++) {
            if (i == numThreads - 1)  threads[i] = new AnalizerThread(frase, i * size, frase.length());
            else threads[i] = new AnalizerThread(frase, i * size, (i * size) + size);
            threads[i].start();
        }

        //Esperamos a que todos los threads terminen
        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println(data);
    }
}
