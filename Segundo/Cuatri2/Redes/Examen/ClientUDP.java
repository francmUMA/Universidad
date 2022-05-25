import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.nio.charset.Charset;

/**
 *
 * @author <su nombre aquí>
 */

public class ClientUDP {
    public static void main(String[] args) throws IOException {
        // DATOS DEL SERVIDOR:
        //* FIJOS: coméntelos si los lee de la línea de comandos
        String serverName = "127.0.0.1"; //direccion local
        int serverPort = 54322;
        //* VARIABLES: descoméntelos si los lee de la línea de comandos
        //String serverName = args[0];
        //int serverPort = Integer.parseInt(args[1]);

        DatagramSocket serviceSocket = null;

        //* COMPLETAR: crear socket
        serviceSocket = new DatagramSocket(serverPort);

        // INICIALIZA ENTRADA POR TECLADO
        BufferedReader stdIn = new BufferedReader( new InputStreamReader(System.in) );
        String userInput;
        System.out.println("Introduzca un texto a enviar (0 para acabar): ");
        userInput = stdIn.readLine(); /*CADENA ALMACENADA EN userInput*/

        //* COMPLETAR: Comprobar si el usuario quiere terminar servicio
        while (userInput.compareTo("0") != 0)
        {
            //* COMPLETAR: Crear datagrama con la cadena escrito en el cuerpo
            DatagramPacket envio = new DatagramPacket(userInput.getBytes(), userInput.length(), InetAddress.getByName(serverName), 12500);
            //* COMPLETAR: Enviar datagrama a traves del socket
            serviceSocket.send(envio);
            System.out.println("STATUS: Waiting for the reply");

            //* COMPLETAR: Crear e inicializar un datagrama VACIO para recibir la respuesta de máximo 500 bytes
            DatagramPacket recepcion = new DatagramPacket(new byte[500], 500);

            //* COMPLETAR: Recibir datagrama de respuesta
            serviceSocket.receive(recepcion);

            //* COMPLETAR: Extraer contenido del cuerpo del datagrama en variable line
            String line = null;
            line = new String(recepcion.getData());

            System.out.println("echo: " + line);
            System.out.println("Introduzca un texto a enviar (0 para acabar): ");
            userInput = stdIn.readLine();
        }

        System.out.println("STATUS: Closing client");

        //* COMPLETAR Cerrar socket cliente
        serviceSocket.close();

        System.out.println("STATUS: closed");
    }
}
