package peterson03;
//¿Exclusión mutua?¿Ausencia de LiveLock?¿Puedes entrar siempre en tu SC?¿Requisito de Justicia?

public class Peterson {
    public volatile int turno = 0;
    public volatile boolean f0 = false; // Empieza siendo cero porque no queremos entrar en la sección crítica
    public volatile boolean f1 = false; // Empieza siendo cero porque no queremos entrar en la sección crítica

    public void preProt0() {

        // V1
        // f0 = true;
        // while (f1)
        // Thread.yield();

        // V2
        // while (f1)
        // Thread.yield();
        // f0 = true;

        // V3 Probar con 1000 y 500.
        // while (turno == 1)
        // Thread.yield();

        // VEnd
        f0 = true;
        turno = 1;
        while (f1 && turno == 1)
            Thread.yield();
    }

    public void postProt0() {
        // V1, VEnd
        f0 = false;

        // V3
        // turno = 1;
    }

    public void preProt1() {
        // V1
        // f1 = true;
        // while (f0)
        // Thread.yield();

        // V2
        // while (f0)
        // Thread.yield();
        // f1 = true;

        // V3
        // while (turno == 0)
        // Thread.yield();

        // VEnd
        f1 = true;
        turno = 0;
        while (f0 && turno == 0)
            Thread.yield();
    }

    public void postProt1() {
        // V1, V2, VEnd
        f1 = false;

        // V3
        // turno = 0;
    }
}