package EscrituraDistribuida;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class TextEditorClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry();
            TextEditorService server = (TextEditorService) registry.lookup("TextEditorService");
            Scanner sc = new Scanner(System.in);
            System.out.print("Introduce el id: ");
            String id = sc.nextLine();
            sc.close();

            String document = server.getDocument(id);
            System.out.println(document);
            server.insertText(0, "Hola ", id);
            server.saveDocument(id);

            document = server.getDocument(id);
            System.out.println(document);
            server.insertText(5, "mundo", id);
            server.saveDocument(id);

            document = server.getDocument(id);
            System.out.println(document);
            server.deleteText(5, 1, id);
            server.saveDocument(id);

            document = server.getDocument(id);
            System.out.println(document);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
