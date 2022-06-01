package impresoras;
import java.util.ArrayDeque;
import java.util.Queue;

import impresoras.SalaImpresoras;

public class SalaImpresorasML implements SalaImpresoras{

    Queue<Integer> colaClientes = new ArrayDeque<>();
    Queue<Integer> impresorasLibres = new ArrayDeque<>();
    int N;

    public SalaImpresorasML (int N){
        this.N = N;
        for (int i = 0; i < N; i++){
            impresorasLibres.add(i+1);
        }
    }

    @Override
    public synchronized int quieroImpresora(int id) throws InterruptedException {
        colaClientes.add(id);
        while (impresorasLibres.size() == 0 || (colaClientes.peek() != null && colaClientes.peek() != id)){
            wait();
        }
        colaClientes.poll();
        int res = impresorasLibres.poll();
        System.out.println("El cliente " + id + " ha cogido la impresora " + res + ". Quedan " + impresorasLibres.size());
        if (impresorasLibres.size() > 0){
            notifyAll();
        }
        return res;
    }

    @Override
    public synchronized void devuelvoImpresora(int id, int n) throws InterruptedException {
        impresorasLibres.add(n);
        System.out.println("El cliente " + id + " ha liberado la impresora " + n  + ". Quedan " + impresorasLibres.size());
        if (impresorasLibres.size() == 1){
            notifyAll();
        }
    }
    
}
