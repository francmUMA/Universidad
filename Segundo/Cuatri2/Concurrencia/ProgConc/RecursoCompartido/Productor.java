package RecursoCompartido;

public class Productor implements Runnable{

    private RecursoCompartido rc;

    public Productor(RecursoCompartido rc){
        this.rc = rc;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++){
            rc.escribir(i);
        }
    }
    
}
