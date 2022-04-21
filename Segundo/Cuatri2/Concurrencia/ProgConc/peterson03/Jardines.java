package peterson03;

//Problema de la actualización multiple.

//Entran personas al jardín, y el contador, visitantes, se encarga de contar cuantas han entrado (nunca salen).

public class Jardines {
    public static void main(String[] args) throws InterruptedException {
        Contador visitantes = new Contador();
        Peterson p = new Peterson();
        Thread puerta1 = new Thread(new Puerta0(p, visitantes, 1000));
        Thread puerta2 = new Thread(new Puerta1(p, visitantes, 500));
        puerta1.start();
        puerta2.start();

        puerta1.join(); // Esperamos a que terminen las dos hebras para poder imprimir
        puerta2.join();

        System.out.println("Hay " + visitantes.valor() + " visitantes");
    }
}