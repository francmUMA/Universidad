import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class MatrixMultiplyServer extends UnicastRemoteObject implements MatrixMultiplyInterface {
    @Override
    public boolean canBeMultiplied(int[][] A, int[][] B) throws RemoteException {
        return A[0].length == B.length;
    }

    @Override
    public int[][] multiply(int[][] A, int[][] B) throws RemoteException {
        int[][] C = new int[A.length][B[0].length];
        for (int i = 0; i < A.length; i++){
            for (int j = 0; j < B[0].length; j++){
                int val = 0;
                for (int k = 0; k < A[0].length; k++){
                    val += A[i][k] * B[k][j];
                }
                C[i][j] = val;
            }
        }
        return C;
    }

    public MatrixMultiplyServer() throws RemoteException{
        super();
    }

    public static void main(String[] args) {
        try{
            MatrixMultiplyServer server = new MatrixMultiplyServer();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("matrix-multiply", server);
            System.err.println("Server ready");
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
