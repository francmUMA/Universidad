package PrimerasHebras;
public class miPrimeraHebra implements Runnable {

    Character myChar;

    public miPrimeraHebra(Character myChar) {
        this.myChar = myChar;
    }

    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            System.out.print(myChar);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(new miPrimeraHebra('A'));
        Thread t2 = new Thread(new miPrimeraHebra('B'));

        t1.start();
        t2.start();

        t1.join();
        t2.join();
    }
}
