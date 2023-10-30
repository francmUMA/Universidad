package rmicalculator;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CalculatorInterface extends Remote{
    
    float add(float a, float b) throws RemoteException;
    float substract(float a, float b) throws RemoteException;
    float multiply(float a, float b) throws RemoteException;
    float divide(float a, float b) throws RemoteException;
    float power(float a, int b) throws RemoteException;
}
