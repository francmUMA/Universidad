class HebraO extends Thread {
    int[] vector;
    int inicio, fin;
    int operaciones;

    public HebraO(int[] vector, int i, int j) {
        this.vector = vector;
        inicio = i;
        fin = j;
    }

    public void run() {
        OrdenarDivideVenceras.intercambio(vector, inicio, fin);
    }
}
