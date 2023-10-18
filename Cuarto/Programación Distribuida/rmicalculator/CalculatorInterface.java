package rmicalculator;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CalculatorInterface extends Remote{
    int add(int a, int b) throws RemoteException;
    int substract(int a, int b) throws RemoteException;
    int multiply(int a, int b) throws RemoteException;
    int divide(int a, int b) throws RemoteException;
}
