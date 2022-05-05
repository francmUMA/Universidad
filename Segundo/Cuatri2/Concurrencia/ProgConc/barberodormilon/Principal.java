package barberodormilon;

public class Principal {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Barberia b = new Barberia();
		Thread barbero = new Thread(new Barbero(b));
		Thread entorno = new Thread(new Entorno(b));
		barbero.start();
		entorno.start();

	}

}
