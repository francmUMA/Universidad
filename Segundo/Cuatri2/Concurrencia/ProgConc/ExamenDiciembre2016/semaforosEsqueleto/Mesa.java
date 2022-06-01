package semaforosEsqueleto;

import java.util.concurrent.*;
public class Mesa {

	private int N;
	Semaphore espera[];
	Semaphore mutex = new Semaphore(1, true);
	int numJugadores = 0;
	boolean jugadas[];
	int numCaras = 0;
	int numCruces = 0;
	int ganador;

	public Mesa(int N){
		this.N = N;
		espera = new Semaphore[N - 1];
		jugadas = new boolean[N];
		for (int i = 0; i < N - 1; i++){
			espera[i] = new Semaphore(0, true);
		}
		ganador = N;
	}
	
	
	
	/**
	 * 
	 * @param id del jugador que llama al m�todo
	 * @param cara : true si la moneda es cara, false en otro caso
	 * @return un valor entre 0 y N. Si devuelve N es que ning�n jugador 
	 * ha ganado y hay que repetir la partida. Si  devuelve un n�mero menor que N, es el id del
	 * jugador ganador.
	 * 
	 * Un jugador llama al m�todo nuevaJugada cuando quiere poner
	 * el resultado de su tirada (cara o cruz) sobre la mesa.
	 * El jugador deja su resultado y, si no es el �ltimo, espera a que el resto de 
	 * los jugadores pongan sus jugadas sobre la mesa.
	 * El �ltimo jugador comprueba si hay o no un ganador, y despierta
	 * al resto de jugadores
	 *  
	 */
	public int nuevaJugada(int id,boolean cara) throws InterruptedException{
		mutex.acquire();
		int copia = numJugadores;
		numJugadores++;
		if (numJugadores < N){
			mutex.release();
			jugadas[id] = cara;
			espera[copia].acquire();
		} else if (numJugadores == N){
			numJugadores = 0;
			mutex.release();

			//calcular el numero de veces que se ha obtenido cara o cruz
			for(int i = 0; i < N; i++){
				if (jugadas[i]){
					numCaras++;
				} else {
					numCruces++;
				}
			}

			if (numCaras == 1){
				//buscar cual es el jugador que ha obtenido cara
				boolean enc = false;
				for (int i = 0; i < N && !enc; i++){
					if (jugadas[i]){
						ganador = i;
						enc = true;
					}
				}
			} else if (numCruces == 1){
				//buscar cual es el jugador que ha obtenido cara
				boolean enc = false;
				for (int i = 0; i < N && !enc; i++){
					if (!jugadas[i]){
						ganador = i;
						enc = true;
					}
				}
			}
			-System.out.println("El ganador es: " + ganador);
			for (int i = 0; i < N - 1; i++){
				espera[i].release();
			}
			
		}
		
		return ganador;
	}
}
