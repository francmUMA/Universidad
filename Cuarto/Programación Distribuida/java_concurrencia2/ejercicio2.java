package java_concurrencia2;

import java.util.Random;

public class ejercicio2 {
    public static class Jugador extends Thread{
        private int resultado;
        private int id;

        public Jugador(int id) {
            this.id = id;
        }

        public void run() {
            dado1.lanzarDados();
            dado2.lanzarDados();
            System.out.println("Jugador " + id + " lanza los dados");
            System.out.println("Obtiene " + dado1.getResultado() + " y " + dado2.getResultado());
            resultado = dado1.getResultado() + dado2.getResultado();
            dado1.cederDado();
            dado2.cederDado();
        }

        public int getResultado() {
            return resultado;
        }
    }

    public static class Dados{
        private int resultado;
        private boolean disponible;
        
        public Dados() {
            this.disponible = true;
        }

        public synchronized void lanzarDados() {
            if (!disponible) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            disponible = false;
            Random rand = new Random();
            resultado = rand.nextInt(6) + 1;
        }

        public synchronized void cederDado(){
            disponible = true;
            notify();
        }

        public int getResultado() {
            return resultado;
        }
    }

    static Dados dado1 = new Dados();
    static Dados dado2 = new Dados();

    public static void main(String[] args) {
        Thread jugador1 = new Jugador(1);
        Thread jugador2 = new Jugador(2);

        jugador1.start();
        jugador2.start();

        try {
            jugador1.join();
            jugador2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        
        if (((Jugador)jugador1).getResultado() > ((Jugador)jugador2).getResultado()) {
            System.out.println("Gana jugador 1");
        } else if (((Jugador)jugador1).getResultado() < ((Jugador)jugador2).getResultado()) {
            System.out.println("Gana jugador 2");
        } else {
            System.out.println("Empate");
        }
    }
}
