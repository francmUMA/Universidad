package mvc;

public class NoesSies {
    private int no = 0;
    private int si = 0;

    public void incrSi() {
        si++;
    }

    public void incrNo() {
        no++;
    }

    public String toString() {
        return "Si: " + si + " No:" + no;
    }
}
