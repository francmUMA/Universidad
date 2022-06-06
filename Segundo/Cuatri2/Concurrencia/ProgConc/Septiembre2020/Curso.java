import java.util.concurrent.Semaphore;

public class Curso {

	Semaphore mutex = new Semaphore(1, true);
	Semaphore haySitioIndividual = new Semaphore(1, true);
	Semaphore haySitioGrupal = new Semaphore(1, true);
	Semaphore formandoGrupo = new Semaphore(1, true);
	Semaphore alumnosAvanzada[];
	int alumnosEsperaGrupo = 0;
	int alumnosFinAvanzada = 0;
	int alumnosIndividual = 0;

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	public Curso(){
		alumnosAvanzada = new Semaphore[ALUMNOS_AV];
		for (int i = 0; i< ALUMNOS_AV - 1; i++){
			alumnosAvanzada[i] = new Semaphore(0, true);
		}
		alumnosAvanzada[ALUMNOS_AV - 1] = new Semaphore(1, true);
	}

	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		haySitioIndividual.acquire();

		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");
		mutex.acquire();
		alumnosIndividual++;
		if (alumnosIndividual < MAX_ALUMNOS_INI){
			//Si hay menos de 10 alumnos cursando la parte de iniciacion, se libera el semaforo
			haySitioIndividual.release();
		}
		mutex.release();
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");

		//Libera la conexion para que otro alumno pueda usarla
		mutex.acquire();
		if (alumnosIndividual == MAX_ALUMNOS_INI){
			haySitioIndividual.release();
		}
		alumnosIndividual--;
		mutex.release();
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		formandoGrupo.acquire();
		//Espera a que haya tres alumnos conectados
		mutex.acquire();
		int copia = alumnosEsperaGrupo;
		alumnosEsperaGrupo++;
		if (alumnosEsperaGrupo < ALUMNOS_AV){
			//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo
			System.out.println("PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
			formandoGrupo.release();
		}
		mutex.release();
		alumnosAvanzada[copia].acquire();
		mutex.acquire();
		if (alumnosEsperaGrupo == ALUMNOS_AV){
			mutex.release();
			//Espera a que haya un grupo de 3 alumnos conectados
			haySitioGrupal.acquire();

			//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
			System.out.println("PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
			for (int i = 0; i < ALUMNOS_AV - 1; i++){
				alumnosAvanzada[i].release();
			}
		}
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		mutex.acquire();
		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen
		System.out.println("PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
		alumnosFinAvanzada++;
		if (alumnosFinAvanzada == ALUMNOS_AV){
			alumnosAvanzada[ALUMNOS_AV - 1].release();
			//Si ya no hay ningun alumno esperando, se libera el semaforo
			haySitioGrupal.release();
			//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
			System.out.println("PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
			formandoGrupo.release();
			alumnosEsperaGrupo = 0;
			alumnosFinAvanzada = 0;
		}
		mutex.release();
	}
}
