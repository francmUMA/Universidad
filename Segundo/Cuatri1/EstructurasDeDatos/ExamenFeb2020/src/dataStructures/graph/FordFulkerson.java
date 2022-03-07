/**
 * Student's name:
 *
 * Student's group:
 */

package dataStructures.graph;

import dataStructures.list.LinkedList;
import dataStructures.list.List;
import dataStructures.set.HashSet;
import dataStructures.set.Set;
import dataStructures.tuple.Tuple2;

public class FordFulkerson<V> {
    private WeightedDiGraph<V,Integer> g; // Initial graph
    private List<WDiEdge<V,Integer>> sol; // List of edges representing maximal flow graph
    private V src; 			  // Source
    private V dst; 		  	  // Sink

    /**
     * Constructors and methods
     */

    public static <V> int maxFlowPath(List<WDiEdge<V,Integer>> path) {
        int menor = Integer.MAX_VALUE;
        for (WDiEdge<V,Integer> wd : path){
            if (wd.getWeight() < menor){
                menor = wd.getWeight();
            }
        }
        return menor;
    }

    public static <V> List<WDiEdge<V,Integer>> updateEdge(V x, V y, Integer p, List<WDiEdge<V,Integer>> edges) {
        List<WDiEdge<V,Integer>> newEdges = new LinkedList<>();
        newEdges = edges;
        boolean stop = false;
        for (int i = 0; i < newEdges.size() && !stop; i++){
            if (newEdges.get(i).getSrc() == x && newEdges.get(i).getDst() == y){
                stop = true;
                int newWeight = newEdges.get(i).getWeight() + p;
                if (newWeight != 0){
                    newEdges.insert(i, new WDiEdge<>(x,newWeight,y));
                }
            }
        }
        if (!stop){
            newEdges.insert(newEdges.size() - 1, new WDiEdge<>(x,p,y));
        }
        return newEdges;
    }

    public static <V> List<WDiEdge<V,Integer>> updateEdges(List<WDiEdge<V,Integer>> path, Integer p, List<WDiEdge<V,Integer>> edges) {
        List<WDiEdge<V, Integer>> newEdges = edges;
        for (WDiEdge<V, Integer> wd : path){
            newEdges = updateEdge(wd.getSrc(), wd.getDst(), p, newEdges);
        }
        return newEdges;
    }

    public static <V> List<WDiEdge<V,Integer>> addFlow(V x, V y, Integer p, List<WDiEdge<V,Integer>> sol) {
        List<WDiEdge<V, Integer>> newSol = sol;
        boolean stop = false;
        for (int i = 0; i < newSol.size(); i++){
            if (newSol.get(i).getSrc() == x && newSol.get(i).getDst() == y){
                newSol.insert(i, new WDiEdge<>(x, p + newSol.get(i).getWeight(), y));
                stop = true;
            } else if (newSol.get(i).getSrc() == y && newSol.get(i).getDst() == x){
                int w = newSol.get(i).getWeight();
                stop = true;
                if (w < p){
                    newSol.insert(i, new WDiEdge<>(y, p - w, x));
                } else if (w > p){
                    newSol.insert(i, new WDiEdge<>(y, w - p, x));
                }
            }
        }
        if (!stop){
            newSol.insert(sol.size() - 1, new WDiEdge<>(x, p, y));
        }
        return newSol;
    }

    public static <V> List<WDiEdge<V,Integer>> addFlows(List<WDiEdge<V,Integer>> path, Integer p, List<WDiEdge<V,Integer>> sol) {
        List<WDiEdge<V, Integer>> newEdges = sol;
        for (WDiEdge<V, Integer> wd : path){
            newEdges = addFlow(wd.getSrc(), wd.getDst(), p, newEdges);
        }
        return newEdges;
    }

    public FordFulkerson(WeightedDiGraph<V,Integer> g, V src, V dst) {
        List<WDiEdge<V, Integer>> sol = new LinkedList<>();
        WTraversal<V, Integer> paths = new WeightedBreadthFirstTraversal<>(g, src);
        List<WDiEdge<V, Integer>> path = paths.pathTo(dst);
        WeightedDiGraph<V, Integer> wdg = g;
        while (!path.isEmpty()){
            int mf = maxFlowPath(path);
            List<WDiEdge<V,Integer>> edges = wdg.wDiEdges();
            edges = updateEdges(path, -mf, edges);
            edges = updateEdges(reversePath(path, wdg), mf, edges);
            wdg = new WeightedDictionaryDiGraph<>(wdg.vertices(), edges);
            sol = addFlows(path, mf, sol);
        }
    }

    private List<WDiEdge<V, Integer>> reversePath(List<WDiEdge<V, Integer>> path, WeightedDiGraph<V, Integer> g) {
        WTraversal<V, Integer> reversePaths = new WeightedBreadthFirstTraversal<>(g, dst);
        List<WDiEdge<V, Integer>> reversePath = reversePaths.pathTo(src);
        return reversePath;
    }

    public int maxFlow() {
        // TO DO
        return 0;
    }

    public int maxFlowMinCut(Set<V> set) {
        // TO DO
        return 0;
    }

    /**
     * Provided auxiliary methods
     */
    public List<WDiEdge<V, Integer>> getSolution() {
        return sol;
    }

    /**********************************************************************************
     * A partir de aquí SOLO para estudiantes a tiempo parcial sin evaluación continua.
     * ONLY for part time students.
     * ********************************************************************************/

    public static <V> boolean localEquilibrium(WeightedDiGraph<V,Integer> g, V src, V dst) {
        // TO DO
        return false;
    }
    public static <V,W> Tuple2<List<V>,List<V>> sourcesAndSinks(WeightedDiGraph<V,W> g) {
        // TO DO
        return null;
    }

    public static <V> void unifySourceAndSink(WeightedDiGraph<V,Integer> g, V newSrc, V newDst) {
        // TO DO
    }
}
