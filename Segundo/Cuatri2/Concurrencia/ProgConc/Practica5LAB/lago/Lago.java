package lago;

public class Lago {
	private volatile int nivel = 0;
	private Peterson rios = new Peterson();
	private Peterson presas = new Peterson();
	private Peterson rio_presa = new Peterson();

	public Lago(int valorInicial) {
		nivel = valorInicial;
	}

	// f0IncDec, f0Inc
	public void incRio0() {
		rios.preProt0();
		rio_presa.preProt0();
		nivel++;
		rio_presa.postProt0();
		rios.postProt0();
	}

	// f0IncDec, f1Inc
	public void incRio1() {
		rios.preProt1();
		rio_presa.preProt0();
		nivel++;
		rio_presa.postProt0();
		rios.postProt0();
	}

	// f1IncDec, f0Dec
	public void decPresa0() {
		while (nivel < 1) {
			Thread.yield();
		}
		presas.preProt0();
		rio_presa.preProt1();
		nivel--;
		rio_presa.postProt1();
		presas.postProt0();
	}

	// f1IncDec, f1Dec
	public void decPresa1() {
		while (nivel < 1) {
			Thread.yield();
		}
		presas.preProt1();
		rio_presa.preProt1();
		nivel--;
		rio_presa.postProt1();
		presas.postProt1();
		
	}

	public int nivel() {
		return nivel;
	}

}
