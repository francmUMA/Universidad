package VotoDistribuido;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Semaphore;

public class VotingServer extends UnicastRemoteObject implements VotingService{

    private Map<String, Integer> candidates;
    private Semaphore semaphore = new Semaphore(1);

    public VotingServer() throws RemoteException {
        super();
        this.candidates = new HashMap<>();
        semaphore = new Semaphore(1);
    }

    @Override
    public int vote(String candidate) throws RemoteException {
        try {
            semaphore.acquire();
            if (candidates.containsKey(candidate)) {
                candidates.put(candidate, candidates.get(candidate) + 1);
            } else {
                candidates.put(candidate, 1);
            }
            int candidateVotes = candidates.get(candidate);
            semaphore.release();
            return candidateVotes;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return 0;
    }

    @Override
    public int getCount(String candidate) throws RemoteException {
        try {
            semaphore.acquire();
            int candidateVotes = candidates.get(candidate);
            semaphore.release();
            return candidateVotes;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return 0;
    }

    @Override
    public List<String> getAllCandidates() throws RemoteException {
        try {
            semaphore.acquire();
            List<String> candidatesList = new LinkedList<>(candidates.keySet());
            semaphore.release();
            return candidatesList;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void removeVotes() throws RemoteException {
        try {
            semaphore.acquire();
            for (String candidate : candidates.keySet()) {
                candidates.put(candidate, 0);
            }
            semaphore.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void removeVotesAndCandidates() throws RemoteException {
        try {
            semaphore.acquire();
            candidates.clear();
            semaphore.release();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Map<String, Integer> getVotingInformation() throws RemoteException {
        try {
            semaphore.acquire();
            Map<String, Integer> candidatesCopy = new HashMap<>(candidates);
            semaphore.release();
            return candidatesCopy;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }
    
    public static void main(String[] args) {
        try {
            VotingServer votingServer = new VotingServer();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("VotingService", votingServer);
            System.out.println("Voting server ready");
        } catch (Exception e) {
            System.out.println("Voting server main " + e.getMessage());
        }
    }
    
}
