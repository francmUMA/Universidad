import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class MatrixParallelMultiply extends UnicastRemoteObject implements MatrixMultiplyInterface {

        public MatrixParallelMultiply()  throws  RemoteException{
            super();
        }
        //@Override
        public boolean canBeMultiplied(int[][] A, int[][] B) throws RemoteException{
            return A[0].length == B.length;
        }

        private void cellCalc(int id, int[][] A, int[][] B, int[][] C) {
            int val = 0;
            int i = id / B[0].length;
            int j = id % B[0].length;
            for (int k = 0; k < A[0].length; k++){
                val += A[i][k] * B[k][j];
            }
            C[i][j] = val;
        }

        //@Override
        public int[][] multiply(int[][] A, int[][] B) throws RemoteException{
            int[][] C = new int[A.length][B[0].length];
            ExecutorService pool = Executors.newFixedThreadPool(A.length * B[0].length);
            for (int i = 0; i < A.length * B[0].length; i++){
                final int id = i;
                pool.execute(() -> cellCalc(id, A, B, C));
            }
            pool.shutdown();
            return C;
        }

        public static void main(String[] args) {
            try{
                MatrixParallelMultiply server = new MatrixParallelMultiply();
                //int[][] A = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
                //int[][] C = server.multiply(A, A);

                Registry registry = LocateRegistry.createRegistry(1098);
                registry.rebind("matrix-parallel-multiply", server);
                System.err.println("Servidor de calculo de matrices en paralelo ready");
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }

