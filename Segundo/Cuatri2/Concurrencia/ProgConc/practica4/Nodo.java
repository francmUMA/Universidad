import java.util.ArrayList;
import java.util.List;

public class Nodo implements Runnable{
    private List<Integer> lista;

    public Nodo(List<Integer> lista){
        this.lista = lista;
    }

    private void aniade (List<Integer> l, int desde, int hasta){
        for (int i = desde; i < hasta; i++){
            l.add(lista.get(i));
        }
    }

    private void mezcla (List<Integer> l1, List<Integer> l2){
        List<Integer> aux = new ArrayList<>();
    }

    @Override
    public void run() {
        
    }
}
