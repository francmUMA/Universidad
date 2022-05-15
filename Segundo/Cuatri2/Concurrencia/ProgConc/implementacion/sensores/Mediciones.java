package sensores;

import java.util.concurrent.Semaphore;

public class Mediciones {
    private Semaphore trabajando = new Semaphore(0, true);
    private Semaphore scNMediciones = new Semaphore(1, true);
    private Semaphore[] s = {new Semaphore(0, true), new Semaphore(0, true), new Semaphore(0, true)};
    int scSensores = 0;

    public Mediciones() {
        
    }

    /**
     * El sensor id deja su medición y espera hasta que el trabajador
     * ha terminado sus tareas
     * 
     * @param id
     * @throws InterruptedException
     */
    public void nuevaMedicion(int id) throws InterruptedException{
        scNMediciones.acquire();
        scSensores++;
        System.out.println("Sensor " + id + " deja sus mediciones.");
        if (scSensores == 3){
            trabajando.release();
        }
        scNMediciones.release();
        s[id].acquire();
    }

    /***
     * El trabajador espera hasta que están las tres mediciones
     * 
     * @throws InterruptedException
     */
    public void leerMediciones() throws InterruptedException{
        trabajando.acquire();
        System.out.println("El trabajador tiene sus mediciones...y empieza sus tareas");
    }

    /**
     * El trabajador indica que ha terminado sus tareas
     */
    public void finTareas() throws InterruptedException{
        scNMediciones.acquire();
        System.out.println("El trabajador ha terminado sus tareas");
        scSensores = 0;
        scNMediciones.release();
        for (int i = 0; i < 3; i++){
            s[i].release();
        }
    }

}
