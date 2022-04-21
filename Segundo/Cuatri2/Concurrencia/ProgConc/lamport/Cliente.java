package lamport;

class Cliente implements Runnable {
    private int id;
    private Panaderia pan;

    public Cliente(int id, Panaderia pan) {
        this.id = id;
        this.pan = pan;
    }

    public void run() {

        pan.cogerTurno(id);
        System.out.println("el cliente" + id + " coge turno");

        pan.esperoTurno(id);
        pan.inc();
        System.out.println("el cliente" + id + " es atendido por el dependiente");

        pan.salgoPanaderia(id);
        System.out.println("el cliente" + id + " sale de la panadería");

    }
}