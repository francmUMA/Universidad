class HebraInterleaving extends Thread {
    char toPrint;

    public HebraInterleaving(char toPrint) {
        this.toPrint = toPrint;
    }

    public void run() {
        for (int index = 0; index < 5; index++) {
            System.out.println(toPrint);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

    }
}