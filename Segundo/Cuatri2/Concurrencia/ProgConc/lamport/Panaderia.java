package lamport;

//Coger turno no es en exlusion mutua

public class Panaderia { // Recurso
    private int[] turno;
    private int contadorPersonas = 0;
    // private boolean[] cogiendoTurno;

    public Panaderia(int numeroClientes) {
        turno = new int[numeroClientes];
        for (int i = 0; i < turno.length; i++) {
            turno[i] = 0;// el cliente i no quiere entrar en la panaderia
        }
        // cogiendoTurno = new boolean[numeroClientes];
        // for (int i = 0; i < cogiendoTurno.length; i++)
        // cogiendoTurno[i] = true;

    }

    public void cogerTurno(int id) {
        //cogiendoTurno[id] = true;
        int max = 0;
        for (int i = 0; i < turno.length; i++) {
            if (max < turno[i])
                max = turno[i];
        }
        turno[id] = max + 1;
        //cogiendoTurno[id] = false;
    }

    public boolean meToca(int id, int i) {
        // devuelve true sii le toca a id antes que a i
        if ((turno[id] == 0) || (turno[i] != 0 && turno[i] < turno[id]))
            return false;
        else if (turno[i] == turno[id] && i < id)
            return false;
        return true;
    }

    public void esperoTurno(int id) {
        for (int i = 0; i < turno.length; i++) {
           // while (cogiendoTurno[i]) Thread.yield();
            while (!meToca(id, i)) Thread.yield();
        }
    }

    public void inc() {
        contadorPersonas++;
    }

    public int contador() {
        return contadorPersonas;
    }

    public void salgoPanaderia(int id) {
        turno[id] = 0;
    }
}
