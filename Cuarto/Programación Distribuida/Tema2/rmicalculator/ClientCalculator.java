package rmicalculator;


import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ClientCalculator {
    public static void main(String[] args) {
        try{
            Registry registry = LocateRegistry.getRegistry();
            CalculatorInterface calculator = (CalculatorInterface) registry.lookup("Calculator");
            int a = 5;
            int b = 3;
            System.out.println("a = " + a + ", b = " + b);
            System.out.println("a + b = " + calculator.add(a, b));
            System.out.println("a - b = " + calculator.substract(a, b));
            System.out.println("a * b = " + calculator.multiply(a, b));
            System.out.println("a / b = " + calculator.divide(a, b));
        } catch (Exception e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
}
