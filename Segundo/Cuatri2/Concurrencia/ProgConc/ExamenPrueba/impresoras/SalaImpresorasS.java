package impresoras;

import java.util.concurrent.Semaphore;

public class SalaImpresorasS implements SalaImpresoras{

    private int N;
    Semaphore mutex = new Semaphore(1, true);
    boolean impresoras[];
    int impresorasLibres;
    Semaphore hayLibres = new Semaphore(1, true);

    public SalaImpresorasS (int N){
        this.N = N;
        impresorasLibres = N;
        impresoras = new boolean[N];
        for (int i = 0; i < N; i++){
            impresoras[i] = false;
        }
    }

    @Override
    public int quieroImpresora(int id) throws InterruptedException {
        hayLibres.acquire();
        mutex.acquire();
        boolean enc = false;
        int res = 0;
        for (int i = 0; i < N && !enc;  i++){
            if (!impresoras[i]){
                res = i + 1; 
                impresoras[i] = true;
                impresorasLibres--;
                enc = true;
            }
        }
        System.out.println("El cliente " + id + " ha cogido la impresora " + res + ". Quedan: " + impresorasLibres);
        if (impresorasLibres > 0){
            hayLibres.release();
        }
        mutex.release();
        return res;
    }

    @Override
    public void devuelvoImpresora(int id, int n) throws InterruptedException {
        mutex.acquire();
        if (impresorasLibres == 0){
            hayLibres.release();
        }
        impresorasLibres++;
        impresoras[n - 1] = false;
        System.out.println("El cliente " + id + " ha liberado la impresora " + n + ".Quedan " + impresorasLibres);
        mutex.release();
    }
    
}
