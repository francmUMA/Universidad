package rmicalculator;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;


public class ServerCalculator extends UnicastRemoteObject implements CalculatorInterface{
    private static final long serialVersionUID = 1L;

    protected ServerCalculator() throws RemoteException {
        super();
    }

    @Override
    public int add(int a, int b) throws RemoteException {
        return a + b;
    }

    @Override
    public int substract(int a, int b) throws RemoteException {
        return a - b;
    }

    @Override
    public int multiply(int a, int b) throws RemoteException {
        return a * b;
    }

    @Override
    public int divide(int a, int b) throws RemoteException {
        return a / b;
    }

    public static void main(String[] args) {
        try{
            ServerCalculator server = new ServerCalculator();
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("Calculator", server);
            System.err.println("Calculator server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}