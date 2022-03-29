package Jardin;

public class Contador {
    private volatile int cont;

    /*

    Propuesta 1:
    Hacer un array con tantos contadores como hebras se quieran crear (un contador por hebra)
    y al final sumarlo. Para saber el acceso a cada contador, hay que guardar en cada puerta el
    número que se le ha asignado.
    
    */

    public Contador(){
        cont = 0;
    }

    public void inc(){
        cont++;
    }

    public int valor(){
        return cont;
    }
}
