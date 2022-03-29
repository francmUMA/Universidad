package Cuarto;

class OtraHebra extends Thread {
    private int id;
    private UnaHebra h;

    public OtraHebra(int id, UnaHebra h) {
        this.id = id;
        this.h = h;
    }

    public String toString() {
        return "OtraHebra " + id;
    }

    public void run() {
        for (int i = 0; i < 10; i++) {
            h.quienSoy(); // Llama al objeto desde la otra hebra
        }
    }
}