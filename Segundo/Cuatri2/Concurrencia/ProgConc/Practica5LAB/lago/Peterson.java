package lago;
public class Peterson {
    public volatile int turno = 0;
    public volatile boolean f0 = false; // Empieza siendo cero porque no queremos entrar en la sección crítica
    public volatile boolean f1 = false; // Empieza siendo cero porque no queremos entrar en la sección crítica

    public void preProt0() {
        f0 = true;
        turno = 1;
        while (f1 && turno == 1)
            Thread.yield();
    }

    public void postProt0() {
        f0 = false;
    }

    public void preProt1() {
        f1 = true;
        turno = 0;
        while (f0 && turno == 0)
            Thread.yield();
    }

    public void postProt1() {
        f1 = false;
    }
}
