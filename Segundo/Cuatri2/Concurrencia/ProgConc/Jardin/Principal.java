package Jardin;

public class Principal {
    public static void main(String[] args) throws InterruptedException {
        Contador visitantes = new Contador();
        Thread puerta1 = new Thread(new Puerta(visitantes, 1000));
        Thread puerta2 = new Thread(new Puerta(visitantes, 1000));
        puerta1.start();
        puerta2.start();
        Thread.sleep(10);
        System.out.println(visitantes.valor());
    }
}
