package EscrituraDistribuida;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class TextEditorServer extends UnicastRemoteObject implements TextEditorService{

    private String document;
    private boolean writing;
    private String writerID;

    public TextEditorServer() throws RemoteException {
        super();
        this.document = "";
        this.writing = false;
        this.writerID = "";
    }

    @Override
    public String getDocument(String id) throws RemoteException {
        if(!writing){
            writing = true;
            writerID = id;
        } 
        return document;
    }

    @Override
    public void insertText(int position, String text, String id) throws RemoteException {
        if (writerID.equals(id)){
            document = document.substring(0, position) + text + document.substring(position);
        }
    }

    @Override
    public void deleteText(int position, int length, String id) throws RemoteException {
        if (writerID.equals(id)){
            document = document.substring(0, position) + document.substring(position + length);
        }
    }

    @Override
    public void saveDocument(String id) throws RemoteException {
        if (writerID.equals(id)){
            writing = false;
            writerID = "";
        }
    }
    
    public static void main(String[] args) {
        try {
            TextEditorServer server = new TextEditorServer();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("TextEditorService", server);
            System.out.println("Server started");
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
}
