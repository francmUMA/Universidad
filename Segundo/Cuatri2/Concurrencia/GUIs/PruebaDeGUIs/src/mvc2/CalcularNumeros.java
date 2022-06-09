package mvc2;

import java.util.List;
import java.util.Random;

//importa el swing worker de javax
import javax.swing.SwingWorker;

import mvc2.NumeroThreshold;

public class CalcularNumeros extends SwingWorker<Void, Object>{

    private NumeroThreshold modelo;
    private int N;
    private static Random r = new Random();
    private Vista vista;

    public CalcularNumeros(NumeroThreshold modelo, int N, Vista vista){
        this.modelo = modelo;
        this.N = N;
        this.vista = vista;
    }

    public void calcular() {
        for (int i = 0; i < N; i++) {
            try {
                Thread.sleep(100);
                modelo.anyadirNumero(r.nextFloat());
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            
        }
    }

    protected Void doInBackground() {
        calcular();
        return null;
    }

    public void done(){
        List<Float> lf1 = modelo.verListaMenor();
        List<Float> lf2 = modelo.verListaMayor();

        // Imprimir 5 en línea y luego un \n
        for (int i = 0; i < lf1.size(); i++) {
            vista.anyadirListaMenores(String.format("%.02f", lf1.get(i)) + " ");
            if ((i + 1) % 5 == 0)
                vista.anyadirListaMenores("\n");
        }
        for (int i = 0; i < lf2.size(); i++) {
            vista.anyadirListaMayores(String.format("%.02f", lf2.get(i)) + " ");
            if ((i + 1) % 5 == 0)
                vista.anyadirListaMayores("\n");
        }
    }
}
