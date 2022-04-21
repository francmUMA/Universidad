package practica4;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class PrincipalNodo {
    public static void main(String[] args) throws InterruptedException {
        Random r = new Random();

        //Crear lista de numeros random
        int size = r.nextInt(20);
        List<Integer> lista = new ArrayList<>();
        for (int i = 0; i < size; i++){
            lista.add(r.nextInt(50));
        }

        //Creamos un nodo nuevo
        Nodo n = new Nodo(lista);
        Thread t = new Thread(n);
        t.start();
        t.join();

        //Mostramos la lista
        System.out.println("La lista de valores sin ordenar es: " + Arrays.toString(lista.toArray()));
        System.out.println("La lista de valores ordenados es: " + Arrays.toString(n.getLista().toArray()));
    }
}
