package PrimerasHebras;
public class miSegundaHebra extends Thread {
    Character myChar;

    public miSegundaHebra(Character myChar){
        this.myChar = myChar;
    }

    public void run() {
        for (int i = 0; i < 20; i++) {
            System.out.print(myChar);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new Thread(new miPrimeraHebra('A'));
        Thread t2 = new Thread(new miPrimeraHebra('B'));

        miSegundaHebra t3 = new miSegundaHebra('C');

        t2.start();
        t1.start();
        t3.start();
    }
}