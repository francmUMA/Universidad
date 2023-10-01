import java.util.TreeMap;
import java.util.Map;
import java.util.concurrent.Semaphore;

public class Ejercicio7 {
    public static class AnalizerThread extends Thread{
        private String frase;
        private int inicio;
        private int fin;

        public AnalizerThread(String frase, int inicio, int fin){
            this.frase = frase;
            this.inicio = inicio;
            this.fin = fin;
        }

        public void run(){
            for (int i = inicio; i < fin; i++) {
                char c = frase.charAt(i);
                try {
                    mutex.acquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                if (data.containsKey(c)) {
                    data.put(c, data.get(c) + 1);
                }
                mutex.release();
            }
        }

    }

    static Map<Character, Integer> data = new TreeMap<Character, Integer>();
    static Semaphore mutex = new Semaphore(1);
    public static void main(String[] args) {
        String frase = "Módulo 1: Introducción al Arduino" +
        "1.1 ¿ Qué es Arduino y para qué sirve?" +
        "Arduino es una plataforma de hardware de código abierto, basada en una sencilla placa con" +
        "entradas y salidas analógicas y digitales, en un entorno de desarrollo que está basado en el" +
        "lenguaje de programación Processing. Es un dispositivo que conecta el mundo físico, con el" +
        "mundo virtual, o el mundo analógico con el digital." +
        "1.2 Características de Arduino" +
        "Arduino puede tomar la información del entorno físico a través de sus puertos de entrada;" +
        "para ello, toda una gama de sensores se pueden usar para el control de luces, motores," +
        "pantallas y otros actuadores, creando una interfaz de comunicación de un sistema a otro." +
        "El microcontrolador en la placa Arduino se programa mediante el lenguaje de programación" +
        "Arduino (basado en Wiring) y el entorno de desarrollo Arduino (basado en Processing). Los" +
        "proyectos realizados con Arduino pueden ejecutarse sin necesidad de conectarlo a un" +
        "ordenador, si bien tienen la posibilidad de hacerlo y comunicar con diferentes tipos de" +
        "software (por ejemplo, Flash, Processing, MaxMSP)." +
        "1.3 Descargar e instalar Arduino paso a paso" +
        "Por suerte, instalar el software de Arduino en un ordenador con Windows 10 desde cero, no" +
        "requiere de conocimientos avanzados por parte del usuario. Por ende, con tan solo seguir" +
        "los pasos que te detallamos a continuación, lograrás obtener dicho programa en tu PC para" +
        "usarlo libremente en tus próximos proyectos." +
        "Primero que todo, tienes que ingresar a la web oficial de Arduino ( arduino.cc) para acceder" +
        "a la pestaña de “Software” que se encuentra en la parte superior de la página. Por medio de" +
        "esta, en un menú desplegable, encontrarás la opción que indica “Descargas” o “Downloads”" +
        "y desde allí, podrás obtener el archivo de descarga";

        
        int numThreads = 24;
        int size = frase.length() / numThreads;

        Thread[] threads = new AnalizerThread[numThreads];

        data.put('a',0);
        data.put('e',0);
        data.put('i',0);
        data.put('o',0);
        data.put('u',0);


        for (int i = 0; i < numThreads; i++) {
            if (i == numThreads - 1)  threads[i] = new AnalizerThread(frase, i * size, frase.length());
            else threads[i] = new AnalizerThread(frase, i * size, (i * size) + size);
            threads[i].start();
        }

        //Esperamos a que todos los threads terminen
        for (int i = 0; i < numThreads; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println(data);
    }
}
