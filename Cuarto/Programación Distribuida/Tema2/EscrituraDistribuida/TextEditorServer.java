package EscrituraDistribuida;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.concurrent.Semaphore;

public class TextEditorServer extends UnicastRemoteObject implements TextEditorService{

    private String document;
    private boolean writing;
    private String writerID;
    private Semaphore semaphore;

    public TextEditorServer() throws RemoteException {
        super();
        this.document = "";
        this.writing = false;
        this.writerID = "";
        this.semaphore = new Semaphore(1);
    }

    @Override
    public String getDocument(String id) throws RemoteException {
        try {
            semaphore.acquire();
            if(!writing){
                writing = true;
                writerID = id;
            }
            semaphore.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
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
            try {
                semaphore.acquire();
                writing = false;
                semaphore.release();
                writerID = "";
                System.out.println("Document saved. ID: " + writerID);
            } catch (InterruptedException e) {
                e.printStackTrace();
                System.out.println("Error: Cant save document. ID: " + writerID);
            }
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
