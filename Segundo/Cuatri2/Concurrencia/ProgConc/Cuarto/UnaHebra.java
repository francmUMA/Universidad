
package Cuarto;

class UnaHebra extends Thread {
    private int id;

    public UnaHebra(int id) {
        this.id = id;
    }

    public void quienSoy() {
        System.out.println(Thread.currentThread());
    }

    public String toString() {
        return "Hebra " + id;
    }

    public void run() {
        for (int i = 0; i < 10; i++) {
            quienSoy();
        }
    }
}
