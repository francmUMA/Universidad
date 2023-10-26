package RMIchat;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.List;

public class ChatServer extends UnicastRemoteObject implements ChatService {
    private List<String> messages;

    public ChatServer() throws RemoteException{
        super();
        this.messages = new LinkedList<String>();
    }

    @Override
    public void sendMessage(String sender, String message) throws RemoteException {
        this.messages.add(sender + ": " + message);
    }

    @Override
    public List<String> receiveMessage() throws RemoteException {
        return this.messages;
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
