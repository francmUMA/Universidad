package RecursoCompartido;

public class Consumidor implements Runnable{

    private RecursoCompartido rc;

    public Consumidor(RecursoCompartido rc){
        this.rc = rc;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++){
            rc.leer();
        }
    }
    
}
