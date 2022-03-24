public class Interleaving {

    public static void main(String[] args) {

        HebraInterleaving o1 = new HebraInterleaving('A');
        HebraInterleaving o2 = new HebraInterleaving('B');
        HebraInterleaving o3 = new HebraInterleaving('C');

        o1.start();
        o2.start();
        o3.start();

        try {
            o1.join();
            o2.join();
            o3.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }
}