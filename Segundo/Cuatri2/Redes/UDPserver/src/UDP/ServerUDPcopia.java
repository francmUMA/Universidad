package UDP;


import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

/**
 *
 * @author Francisco Javier Cano Moreno
 */
public class ServerUDPcopia {
    public static String capitalize(String s){
        String words[] = s.split("\\s");
        String res = "";
        for(String w: words){
            if(!res.isEmpty()){
                res += " ";
            }
            res += w.substring(0,1).toUpperCase() + w.substring(1);
        }
        return res;
    }

    public static void main(String[] args)
    {
        // DATOS DEL SERVIDOR
        //* FIJO: Si se lee de línea de comando debe comentarse
        int port = 54323; // puerto del servidor
        //* VARIABLE: Si se lee de línea de comando debe descomentarse
        //int port = Integer.parseInt(args[0]); // puerto del servidor
        byte message[] = new byte[400];

        // SOCKET
        DatagramSocket server = null;

        //* COMPLETAR Crear e inicalizar el socket del servidor
        try {
            server = new DatagramSocket(port);
            System.out.println("Socket creado");
        } catch (SocketException e) {
            System.err.println("Error creando el socket " + e.getMessage());
        }

        String line = "";

        // Funcion PRINCIPAL del servidor
        while (line.compareTo("0") == 0)
        {
            //* COMPLETAR: Crear e inicializar un datagrama VACIO para recibir la respuesta de máximo 500 bytes
            DatagramPacket datagram = null;
            try {
                datagram = new DatagramPacket(message,message.length);
                System.out.println("Datagrama de recepcion creado");
            } catch (Exception e) {
                System.err.println("Error al crear el datagrama " + e.toString());
            }

            //* COMPLETAR: Recibir datagrama
            try {
                server.receive(datagram);
                System.out.println("Datagrama recibido");
            } catch (IOException e) {
                // TODO Auto-generated catch block
                System.err.println("Error al recibir el datagrama");
            }

            //* COMPLETAR: Obtener texto recibido
            line = new String(datagram.getData());

            //* COMPLETAR: Mostrar por pantalla la direccion socket (IP y puerto) del cliente y su texto
            System.out.println("He recibido:" + line +
                    "\n de: " + datagram.getAddress().getHostAddress() +
                    "\n por el puerto: " + datagram.getPort());

            // Capitalizamos la linea
            line = capitalize(line);

            //* COMPLETAR: crear datagrama de respuesta
            DatagramPacket respuesta = null;
            try {
                respuesta = new DatagramPacket(line.getBytes(), line.length(), datagram.getAddress(), 53232);
            } catch (Exception e) {
                //TODO: handle exception
                System.err.println("Error al crear el datagrama de respuesta " +  e.toString());
            }
            //* COMPLETAR: Enviar datagrama de respuesta
            try {
                server.send(respuesta);
                System.out.println("Datagrama de respuesta enviado");
            } catch (IOException e) {
                // TODO Auto-generated catch block
                System.err.println("Error al enviar el datagrama de respuesta");
            }

        } // Fin del bucle del servicio
        server.close();

    }

}
