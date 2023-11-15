import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MatrixMultiplyClient {
    public static void main(String[] args) {
        try{
            Registry registry1 = LocateRegistry.getRegistry(1098);
            Registry registry2 = LocateRegistry.getRegistry(1099);
            MatrixMultiplyInterface matrixMultiply = (MatrixMultiplyInterface) registry2.lookup("matrix-multiply");
            MatrixMultiplyInterface matrixParallelMultiply = (MatrixMultiplyInterface) registry1.lookup("matrix-parallel-multiply");
            int[][] c1 = matrixMultiply.multiply(new int[][]{{1, 2, 3}, 
                                                             {1, 2, 3}, 
                                                             {1, 2, 3}},

                                                 new int[][]{{1, 2, 3}, 
                                                             {1, 2, 3}, 
                                                             {1, 2, 3}});
                                                             
            int[][] c2 = matrixParallelMultiply.multiply(new int[][]{{1, 2, 3}, 
                                                                     {1, 2, 3}, 
                                                                     {1, 2, 3}}, 
                                                         new int[][]{{1, 2, 3}, 
                                                                     {1, 2, 3}, 
                                                                     {1, 2, 3}});
            for (int i = 0; i < c1.length; i++){
                for (int j = 0; j < c1[0].length; j++){
                    System.out.print(c1[i][j] + " ");
                }
                System.out.println();
            }
            System.out.println();
            for (int i = 0; i < c2.length; i++){
                for (int j = 0; j < c2[0].length; j++){
                    System.out.print(c2[i][j] + " ");
                }
                System.out.println();
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
