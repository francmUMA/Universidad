package EscrituraDistribuida;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface TextEditorService extends Remote{
    String getDocument(String id) throws RemoteException;
    void insertText(int position, String text, String id) throws RemoteException;
    void deleteText(int position, int length, String id) throws RemoteException;
    void saveDocument(String id) throws RemoteException;
}
