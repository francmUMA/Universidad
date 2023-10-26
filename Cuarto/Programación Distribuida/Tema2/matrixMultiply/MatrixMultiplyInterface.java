import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MatrixMultiplyInterface extends Remote {
    boolean canBeMultiplied(int [][]A, int [][]B) throws RemoteException;
    int[][] multiply(int [][]A, int [][]B) throws RemoteException;
}