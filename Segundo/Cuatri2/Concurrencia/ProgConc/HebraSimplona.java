
public class HebraSimplona implements Runnable{

    Character myChar;

    public HebraSimplona(Character myChar){
        this.myChar = myChar;
    }

    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            System.out.print(myChar);
            try{
                Thread.sleep(10);
            } catch (InterruptedException e){
                e.printStackTrace();
            }
            //Thread.yield();
        }
    }

    public static void main(String[] args) throws InterruptedException{
        Thread h1 = new Thread(new HebraSimplona('A'));
        Thread h2 = new Thread(new HebraSimplona('B'));
        Thread h3 = new Thread(new HebraSimplona('C'));

        h1.setPriority(Thread.MAX_PRIORITY);

        h1.start();
        h2.start();
        h3.start();

        System.out.println(h1.getState());
        h1.join();

        System.out.println(h1.getState());

    }
}
