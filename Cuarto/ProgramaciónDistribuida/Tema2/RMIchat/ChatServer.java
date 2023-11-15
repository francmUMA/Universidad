package RMIchat;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;

public class ChatServer extends UnicastRemoteObject implements ChatService {
    private List<String> messages;
    private Semaphore semaphore;

    public ChatServer() throws RemoteException{
        super();
        this.messages = new LinkedList<String>();
        this.semaphore = new Semaphore(1);
    }

    @Override
    public void sendMessage(String sender, String message) throws RemoteException {
        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.messages.add(sender + ": " + message);
        semaphore.release();
    }

    @Override
    public List<String> receiveMessage() throws RemoteException {
        try {
            semaphore.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        List<String> result = new LinkedList<String>(this.messages);
        semaphore.release();
        return result;
    }
    
    public static void main(String[] args) {
        try {
            ChatServer server = new ChatServer();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("ChatService", server);
            System.out.println("ChatServer started");
        } catch (Exception e) {
            System.out.println("ChatServer error: " + e.getMessage());
        }
    }
}
