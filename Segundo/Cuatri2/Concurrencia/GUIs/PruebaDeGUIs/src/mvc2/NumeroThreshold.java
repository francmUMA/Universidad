package mvc2;

import java.util.ArrayList;
import java.util.List;

public class NumeroThreshold {

    private float umbral = 0;

    private List<Float> lf1 = new ArrayList<Float>();
    private List<Float> lf2 = new ArrayList<Float>();

    public void establecerUmbral(float um) {
        umbral = um;
    }

    public void anyadirNumero(float f) {
        if (f < umbral)
            lf1.add(f);
        else
            lf2.add(f);
    }

    public List<Float> verListaMenor() {
        return lf1;
    }

    public List<Float> verListaMayor() {
        return lf2;
    }

    public void limpiar() {
        lf1.clear();
        lf2.clear();
    }

}
