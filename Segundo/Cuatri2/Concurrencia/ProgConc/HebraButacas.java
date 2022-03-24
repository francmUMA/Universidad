import java.util.Arrays;

public class HebraButacas extends Thread {
    int[] butacas;
    int id;
    int counter;

    public HebraButacas(int[] butacas, int id) {
        this.butacas = butacas;
        this.id = id;
        counter = 0;
    }

    public void run() {
        for (int i = 0; i < butacas.length; i++) {
            // Caso 1
            //
            // if (butacas[i] == 0) {
            //     try {
            //         Thread.sleep(200);
            //     } catch (InterruptedException e) {
            //         // TODO Auto-generated catch block
            //         e.printStackTrace();
            //     }
            //     butacas[i] = this.id;
            //     counter++;
            // }

            //CAso 2
            if (butacas[i] == 0) {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }

                if (butacas[i] == 0) {
                    butacas[i] = this.id;
                    counter++;
                }
            }

        }
        System.out.println("Hebra con id " + id + " ha reservado " + counter + " asientos.");
    }

    void printButacas() {
        System.out.println(Arrays.toString(butacas));

    }
}
