import java.util.ArrayList;
import java.util.List;

public class Nodo implements Runnable{
    private List<Integer> lista;

    public Nodo(List<Integer> lista){
        this.lista = lista;
    }

    public List<Integer> getLista(){
        return lista;
    }

    private void aniade (List<Integer> l, int desde, int hasta){
        for (int i = desde; i < hasta; i++){
            l.add(lista.get(i));
        }
    }

    private void mezcla (List<Integer> l1, List<Integer> l2){
        List<Integer> aux = new ArrayList<>();
        int size_left_l1 = 0;
        int size_left_l2 = 0;
        while (size_left_l1 < l1.size() || size_left_l2 < l2.size()){
            if (size_left_l1 >= l1.size()){
                aux.add(l2.get(size_left_l2));
                size_left_l2++;
            } else if (size_left_l2 >= l2.size()){
                aux.add(l1.get(size_left_l1));
                size_left_l1++;
            } else {
                if (l1.get(size_left_l1) < l2.get(size_left_l2)){
                    aux.add(l1.get(size_left_l1));
                    size_left_l1++;
                } else {
                    aux.add(l2.get(size_left_l2));
                    size_left_l2++;
                }
            }
        }
        this.lista = aux;
    }

    @Override
    public void run() {
        if (lista.size() > 1){
            List<Integer> l1 = new ArrayList<>();
            aniade(l1, 0, lista.size()/2);
            Nodo n1 = new Nodo(l1);
            List<Integer> l2 = new ArrayList<>();
            aniade(l2, lista.size()/2, lista.size());
            Nodo n2 = new Nodo(l2);
            Thread t1 = new Thread(n1);
            Thread t2 = new Thread(n2);
            t1.start();
            t2.start();
            try {
                t1.join();
                t2.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.mezcla(n1.getLista(),n2.getLista());
        }
    }
}
