package Cuarto;

public class Principal {
    public static void main(String[] args) {
        // Objetos
        UnaHebra h = new UnaHebra(0);
        OtraHebra o = new OtraHebra(1, h);
        // Comienzan las hebras
        h.start();
        o.start();
    }

}
