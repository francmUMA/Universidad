package RecursoCompartido;

public class RecursoCompartido {
    private int recurso;
    private boolean hayDato = false;

    public RecursoCompartido(){}

    public int leer(){
        while (!hayDato) {
            Thread.yield();
        }
        int a = recurso;
        System.out.println("he leído: " +  a);
        hayDato = false;
        return recurso;
    }

    public void escribir(int r){
        while (hayDato) {
            Thread.yield();
        }
        recurso = r;
        System.out.println("Han escrito: " + r);
        hayDato = true;
        
    }
}
