public class Butacas {

    public static void main(String[] args) {

        int asientos[] = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        HebraButacas o1 = new HebraButacas(asientos, 1);
        HebraButacas o2 = new HebraButacas(asientos, 2);
        HebraButacas o3 = new HebraButacas(asientos, 3);

        o1.start();
        o2.start();
        o3.start();

        try {
            o1.join();
            o2.join();
            o3.join();

            o1.printButacas();
            o2.printButacas();
            o3.printButacas();

        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }
}
