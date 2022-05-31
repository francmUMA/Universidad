package juego;
import java.util.concurrent.*;
public class Mesa {
    //0 - piedra, 1 - papel, 2 - tijeras
	Semaphore scReadyPlayers = new Semaphore(1, true);
	int numReadyPlayers = 0;
	Semaphore[] jugadoresEspera = {new Semaphore(0, true), new Semaphore(0, true)};
	boolean ultima = false;
	int res = -1;
	Semaphore mutex = new Semaphore(1, true);
	int numPiedras = 0;
	int numTijeras = 0;
	int numPapeles = 0;
	
	
	/**
	 * 
	 * @param jug jugador que llama al m�todo (0,1,2)
	 * @param juego jugada del jugador (0-piedra,1-papel, 2-tijeras)
	 * @return  si ha habido un ganador en esta jugada se devuelve 
	 *          la jugada ganadora
	 *         o -1, si no ha habido ganador
	 * @throws InterruptedException
	 * 
	 * El jugador que llama a este m�todo muestra su jugada, y espera a que 
	 * est�n la de los otros dos. 
	 * Hay dos condiciones de sincronizaci�n
	 * CS1- Un jugador espera en el m�todo hasta que est�n las tres jugadas
	 * CS2- Un jugador tiene que esperar a que finalice la jugada anterior para
	 *     empezar la siguiente
	 * 
	 */
	public int nuevaJugada(int jug,int juego) throws InterruptedException{
		mutex.acquire();
		if (juego == 0) numPiedras++;
		if (juego == 1) numPapeles++;
		if (juego == 2) numTijeras++;
		mutex.release();
		scReadyPlayers.acquire();
		int n = numReadyPlayers;
		numReadyPlayers++;
		if (numReadyPlayers < 3){
			scReadyPlayers.release();
			jugadoresEspera[n].acquire();
		} else if (numReadyPlayers == 3){
			scReadyPlayers.release();
			ultima = true;
		}

		//Ya se puede jugar
		if (ultima){
			if (numPiedras == 1 && numTijeras == 2) res = 0;
			if (numPapeles == 1 && numPiedras == 2) res = 1;
			if (numTijeras == 1 && numPapeles == 2) res = 2;
			jugadoresEspera[0].release();
			jugadoresEspera[1].release();
			ultima = false;
		}
		return res;
	}
}
