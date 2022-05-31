package semaforosEsqueleto;

import java.util.concurrent.*;
public class Mesa {

	
	public Mesa(int N){
	
	}
	
	
	
	/**
	 * 
	 * @param id del jugador que llama al método
	 * @param cara : true si la moneda es cara, false en otro caso
	 * @return un valor entre 0 y N. Si devuelve N es que ningún jugador 
	 * ha ganado y hay que repetir la partida. Si  devuelve un número menor que N, es el id del
	 * jugador ganador.
	 * 
	 * Un jugador llama al método nuevaJugada cuando quiere poner
	 * el resultado de su tirada (cara o cruz) sobre la mesa.
	 * El jugador deja su resultado y, si no es el último, espera a que el resto de 
	 * los jugadores pongan sus jugadas sobre la mesa.
	 * El último jugador comprueba si hay o no un ganador, y despierta
	 * al resto de jugadores
	 *  
	 */
	public int nuevaJugada(int id,boolean cara) throws InterruptedException{
		
		return 0;
	}
}
