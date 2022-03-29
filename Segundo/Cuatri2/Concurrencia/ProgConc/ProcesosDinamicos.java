//https://docs.oracle.com/javase/8/docs/api/java/lang/Process.html
import java.io.File;
import java.io.IOException;

public class ProcesosDinamicos {

    private static Process start;

    public static void main(String[] args) throws IOException, InterruptedException {
        ProcessBuilder pb = new ProcessBuilder("../ProgramacionEnC/practica3/descifrar.exe", "../ProgramacionEnC/practica3/imagen/imagen2Encriptada.png",
                "../ProgramacionEnC/practica3/imagen/imagen2.png");
        pb.redirectError(new File("SalidaError.txt"));
        pb.redirectOutput(new File("SalidaNormal.txt"));

        Process p = pb.start();
        p.waitFor();
        System.out.println("Salida " + p.exitValue());
    }
}