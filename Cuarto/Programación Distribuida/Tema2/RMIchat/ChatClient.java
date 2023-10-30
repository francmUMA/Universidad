package RMIchat;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class ChatClient {

    public static class Lector extends Thread{
        private List<String> messages;
        private ChatService chatService;
        private boolean stop;

        public Lector(ChatService chatService){
            this.chatService = chatService;
            this.messages = new LinkedList<>();
            this.stop = false;
        }

        public void run(){
            while(!stop){
                try {
                    this.messages = this.chatService.receiveMessage();
                    sleep(1000);
                } catch (Exception e) {
                    System.out.println("Lector error: " + e.getMessage());
                }
            }
        }

        public List<String> getMessages(){
            return this.messages;
        }

        public void stopLector(){
            this.stop = true;
        }
    }
    public static void main(String[] args) {
        try{
            Registry registry = LocateRegistry.getRegistry(1099);
            ChatService chatService = (ChatService) registry.lookup("ChatService");
            System.out.println("ChatClient started");

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter your name: ");
            String name = scanner.nextLine();

            //Crear una hebra que haga peticiones al servidor de mensajes y actualice una lista de mensajes
            Lector lector = new Lector(chatService);
            List<String> messages = new LinkedList<>();
            lector.start();

            //Está en el bucle hasta que el usuario escriba salir
            System.out.print("Enter your message: ");
            String message = scanner.nextLine();
            while(!message.toLowerCase().equals("salir")){
                //Envía el mensaje al servidor
                chatService.sendMessage(name, message);

                //Imprime por pantalla los mensajes recibidos
                System.out.println("-------MENSAJES ENVIADOS-------");
                messages = lector.getMessages();
                for(String m : messages){
                    System.out.println(m);
                }
                System.out.println("-------------------------------");

                //Pide un nuevo mensaje
                System.out.print("Enter your message: ");
                message = scanner.nextLine();
                
            }
            lector.stopLector();
            lector.join();
            scanner.close();           
        } catch (Exception e) {
            System.out.println("ChatClient error: " + e.getMessage());
        }
    }
}
