package interrupcion0;

public class Hebra extends Thread {
    private int i = 0;

    @Override
    public void run() {
        while (!this.isInterrupted()) {
            System.out.println(i);
            i++;
        }

    }

}
