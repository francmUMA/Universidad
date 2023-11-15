package VotoDistribuido;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class VotingClient{
    public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
        try{
            Registry registry = LocateRegistry.getRegistry();
            VotingService votingService = (VotingService) registry.lookup("VotingService");
            System.out.println("Bienvenido al sistema de votación");
            System.out.println("Qué desea realizar:");
            System.out.println("1. Votar");
            System.out.println("2. Ver votos de un candidato");
            System.out.println("3. Ver todos los candidatos");
            System.out.println("4. Ver información de la votación");
            System.out.println("5. Reiniciar votos");
            System.out.println("6. Reiniciar votos y candidatos");
            System.out.println("7. Salir");
            System.out.print("Opción: ");
            int option = scanner.nextInt();
            while(option != 7){
                String candidate = "";
                if (option > 0 && option < 3){
                    System.out.println("Introduzca el nombre del candidato: ");
                    candidate = scanner.next();
                }
                switch(option){
                    case 1:
                        int votes = votingService.vote(candidate);
                        System.out.println("El candidato " + candidate + " tiene " + votes + " votos ahora.");
                        break;
                    case 2:
                        int count = votingService.getCount(candidate);
                        System.out.println("El candidato " + candidate + " tiene " + count + " votos");
                        break;
                    case 3:
                        System.out.println("Los candidatos son: " + votingService.getAllCandidates());
                        break;
                    case 4:
                        System.out.println("La información de la votación es: " + votingService.getVotingInformation());
                        break;
                    case 5:
                        votingService.removeVotes();
                        System.out.println("Se han reiniciado los votos");
                        break;
                    case 6:
                        votingService.removeVotesAndCandidates();
                        System.out.println("Se han reiniciado los votos y los candidatos");
                        break;
                    default:
                        System.out.println("Opción no válida");
                        break;
                }
                Thread.sleep(2000);
                System.out.println("Qué desea realizar a continuación:");
                System.out.println("1. Votar");
                System.out.println("2. Ver votos de un candidato");
                System.out.println("3. Ver todos los candidatos");
                System.out.println("4. Ver información de la votación");
                System.out.println("5. Reiniciar votos");
                System.out.println("6. Reiniciar votos y candidatos");
                System.out.println("7. Salir");
                System.out.print("Opción: ");
                option = scanner.nextInt();
            }
        } catch(Exception e){
            System.out.println("VotingClient exception: " + e.getMessage());
            e.printStackTrace();
        }
        scanner.close();
    }
}
