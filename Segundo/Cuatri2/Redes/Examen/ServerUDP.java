import java.io.IOException;
import java.net.*;
import java.nio.charset.Charset;

/**
 *
 * @author <su nombre aquí>
 */
public class ServerUDP {
    public static String multiplyText(String s){
        String res = "";
        String nString = s.substring(0, 1);
        int n;
        if (nString.compareTo("1") >= 0 && nString.compareTo("9") <= 0){
            n = Integer.parseInt(nString);
            for (int i = 0; i < n; i++){
                res += s.substring(1, s.length());
            }
        } else {
            res = "ERROR";
        }
        return res;
    }

    public static void main(String[] args)
    {
        // DATOS DEL SERVIDOR
        //* FIJO: Si se lee de línea de comando debe comentarse
        // int port = 54322; // puerto del servidor
        //* VARIABLE: Si se lee de línea de comando debe descomentarse
        int port = Integer.parseInt(args[0]); // puerto del servidor

        // SOCKET
        DatagramSocket server = null;

        //* COMPLETAR Crear e inicalizar el socket del servidor
        try {
            server = new DatagramSocket(port);
        } catch (SocketException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        String line = "";

        // Funcion PRINCIPAL del servidor
        while (line.compareTo("0") != 0)
        {
            //* COMPLETAR: Crear e inicializar un datagrama VACIO para recibir la respuesta de máximo 500 bytes
            DatagramPacket recepcion = new DatagramPacket(new byte[500], 500);

            //* COMPLETAR: Recibir datagrama
            try {
                server.receive(recepcion);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            //* COMPLETAR: Obtener texto recibido
            line = new String(recepcion.getData());

            //* COMPLETAR: Mostrar por pantalla la direccion socket (IP y puerto) del cliente y su texto
            System.out.println("He recibido:" + line +
                    "\n de: " + recepcion.getAddress() +
                    "\n por el puerto: " + recepcion.getPort());

            // Capitalizamos la linea
            line = multiplyText(line);

            //* COMPLETAR: crear datagrama de respuesta
            DatagramPacket envio = new DatagramPacket(line.getBytes(), line.length(), recepcion.getAddress(), recepcion
            .getPort());

            //* COMPLETAR: Enviar datagrama de respuesta
            try {
                server.send(envio);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        } // Fin del bucle del servicio
        server.close();
    }

}
