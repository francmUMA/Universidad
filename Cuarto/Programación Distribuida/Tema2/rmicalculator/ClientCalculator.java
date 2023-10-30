package rmicalculator;


import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ClientCalculator {
    public static void main(String[] args) {
        try{
            Registry registry = LocateRegistry.getRegistry(1099);
            CalculatorInterface calculator = (CalculatorInterface) registry.lookup("Calculator");
            float a = 5.0f;
            float b = 2.0f;
            System.out.println("a = " + a + ", b = " + b);
            System.out.println("a + b = " + calculator.add(a, b));
            System.out.println("a - b = " + calculator.substract(a, b));
            System.out.println("a * b = " + calculator.multiply(a, b));
            System.out.println("a / b = " + calculator.divide(a, b));
            System.out.println("a ^ b = " + calculator.power(a, (int) b));
        } catch (Exception e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
    
}
