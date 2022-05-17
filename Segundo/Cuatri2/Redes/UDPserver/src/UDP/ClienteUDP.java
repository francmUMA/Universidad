package UDP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;


public class ClienteUDP {
    public static void main(String[] args) {


        String serverName = "127.0.0.1";
        int serverPort = 54322;
        int port = 53232;

        DatagramSocket serviceSocket = null;

        try {
            serviceSocket = new DatagramSocket(port);
        } catch (SocketException e) {
            System.err.println("Error creando el socket " + e.getMessage());
        }

        String message = "";
        InputStreamReader lector = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(lector);
        while (!message.equals("TERMINAR")) {
            System.out.print("Introduce una linea: ");
            try {
                message = br.readLine();
            } catch (IOException e) {
                System.out.println("Error al leer la línea");
            }
            DatagramPacket datagram = null;
            DatagramPacket respuesta = null;

            try {
                datagram = new DatagramPacket(
                        message.getBytes(),
                        message.length(),
                        InetAddress.getByName(serverName),
                        serverPort
                );
                respuesta = new DatagramPacket(message.getBytes(), message.length());
                System.out.println("Datagrama creado con mensaje: " + message + " con direccion: " + serverName + " al puerto: " + serverPort);
            } catch (Exception e) {
                System.err.println("Error al crear el datagrama" + e.toString());
            }

            try {
                serviceSocket.send(datagram);
                System.out.println("Datagrama enviado correctamente");
            } catch (Exception e) {
                System.err.println("Error al enviar el datagrama" + e.toString());
            }

            try {
                serviceSocket.receive(respuesta);
                String res = new String(respuesta.getData());
                System.out.println("He recibido: " + res);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                System.err.println("Error al recibir el datagrama");
            }
        }
        serviceSocket.close();
    }
}
