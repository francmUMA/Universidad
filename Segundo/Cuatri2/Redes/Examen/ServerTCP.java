import java.io.*;
import java.net.*;

class ServerTCP {
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
        int port = 17500; // puerto del servidor
        //* VARIABLE: Si se lee de línea de comando debe descomentarse
        // int port = Integer.parseInt(args[0]);

        // SOCKETS
        ServerSocket server = null; // Pasivo (recepción de peticiones)
        Socket client = null;       // Activo (atención al cliente)

        // FLUJOS PARA EL ENVÍO Y RECEPCIÓN
        BufferedReader in = null;
        PrintWriter out = null;

        //* COMPLETAR: Crear e inicalizar el socket del servidor (socket pasivo)
        try {
            server = new ServerSocket(port, 10);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        while (true) // Bucle de recepción de conexiones entrantes
        {
            //* COMPLETAR: Esperar conexiones entrantes
            try {
                client = server.accept();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            //* COMPLETAR: Una vez aceptada una conexion, inicializar flujos de entrada/salida del socket conectado
            try {
                in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                out = new PrintWriter(client.getOutputStream(), true);
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            out.println("Estamos conectados.");

            boolean salir = false;
            while(!salir) // Inicio bucle del servicio de un cliente
            {
                //* COMPLETAR: Recibir texto en line enviado por el cliente a través del flujo de entrada del socket conectado
                String line = "";
                try {
                    line = in.readLine();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                //* COMPLETAR: Comprueba si es fin de conexion - SUSTITUIR POR LA CADENA DE FIN enunciado
                if (line.compareTo("END") != 0){
                    line = multiplyText(line);

                    //* COMPLETAR: Enviar texto al cliente a traves del flujo de salida del socket conectado
                    out.println(line);
                } else { // El cliente quiere cerrar conexión, ha enviado END
                    salir = true;
                    out.println("OK");
                }
            } // fin del servicio

            //* COMPLETAR: Cerrar flujos y socket
            try {
                server.close();
                in.close();
                out.close();
                client.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        } // fin del bucle
    } // fin del metodo
}
