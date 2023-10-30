package rmicalculator;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;


public class ServerCalculator extends UnicastRemoteObject implements CalculatorInterface{
    //private static final long serialVersionUID = 1L;

    public ServerCalculator() throws RemoteException {
        super();
    }

    @Override
    public float add(float a, float b) throws RemoteException {
        return a + b;
    }

    @Override
    public float substract(float a, float b) throws RemoteException {
        return a - b;
    }

    @Override
    public float multiply(float a, float b) throws RemoteException {
        return a * b;
    }

    @Override
    public float divide(float a, float b) throws RemoteException {
        return a / b;
    }

    @Override
    public float power(float a, int b) throws RemoteException {
        return (float) Math.pow(a, b);
    }

    public static void main(String[] args) {
        try{
            ServerCalculator server = new ServerCalculator();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.bind("Calculator", server);
            System.err.println("Calculator server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }

    
}