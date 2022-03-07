/**----------------------------------------------
 * -- Estructuras de Datos.  2018/19
 * -- 2º Curso del Grado en Ingeniería [Informática | del Software | de Computadores].
 * -- Escuela Técnica Superior de Ingeniería en Informática. UMA
 * --
 * -- Examen 4 de febrero de 2019
 * --
 * -- ALUMNO/NAME:
 * -- GRADO/STUDIES:
 * -- NÚM. MÁQUINA/MACHINE NUMBER:
 * --
 * ----------------------------------------------
 */

package dataStructures.graph;

import java.util.Iterator;

import dataStructures.dictionary.Dictionary;
import dataStructures.dictionary.HashDictionary;

import dataStructures.set.Set;
import dataStructures.set.HashSet;
import dataStructures.tuple.Tuple2;

public class DictionaryWeightedGraph<V, W extends Comparable<? super W>> implements WeightedGraph<V, W> {

    static class WE<V1, W1 extends Comparable<? super W1>> implements WeightedEdge<V1, W1> {

		V1 src, dst;
        W1 wght;

        WE(V1 s, V1 d, W1 w) {
            src = s;
            dst = d;
            wght = w;
        }

        public V1 source() {
            return src;
        }

        public V1 destination() {
            return dst;
        }

        public W1 weight() {
            return wght;
        }

        public String toString() {
            return "WE(" + src + "," + dst + "," + wght + ")";
        }

		public int hashCode() {
            int hash = 2;
            hash = 31 * hash + src.hashCode();
            hash = 31 * hash + dst.hashCode();
            hash = 31 * hash + wght.hashCode();
            return hash;
        }

		public boolean equals(Object obj) {
            if (obj instanceof WeightedGraph.WeightedEdge<?,?>) {
                if (obj.hashCode() == this.hashCode()){
                    return true;
                }
            }
            return false;
		}
		
		public int compareTo(WeightedEdge<V1, W1> o) {
            if (this.equals(o)){
                return 0;
            } else {
                if (this.hashCode() > o.hashCode()){          //This > o
                    return 1;
                } else {        //This < o
                    return -1;
                }
            }
		}
    }

    /**
     * Each vertex is associated to a dictionary containing associations
     * from each successor to its weight
     */
    protected Dictionary<V, Dictionary<V, W>> graph;

    public DictionaryWeightedGraph() {
        graph = new HashDictionary<>();
    }


    public void addVertex(V v) {
        graph.insert(v, new HashDictionary<>());
    }

    public void addEdge(V src, V dst, W w) {
        //Buscar los vertices en el grafo y si estan añadir en ambos vertices esta union
        //Saber si los vertices estan en el grafo
        boolean srcInGraph = false;
        boolean dstInGraph = false;
        for (V vertex : graph.keys()){
            if (src == vertex){ srcInGraph = true; }
            if (dst == vertex){ dstInGraph = true; }
        }

        //Si los vertices estan en el grafo entonces añade la arista
        if (srcInGraph && dstInGraph){
            for (Tuple2<V, Dictionary<V, W>> tuple : graph.keysValues()) {
                if (tuple._1() == src) {
                    tuple._2().insert(dst, w);
                } else if (tuple._1() == dst) {
                    tuple._2().insert(src, w);
                }
            }
        } else {
            throw new GraphException("Alguno de los vertices no esta en el grafo");
        }
    }

    public Set<Tuple2<V, W>> successors(V v) {
        //Ver si el vertice esta en el grafo
        boolean vInGraph = false;
        for (V vertex : graph.keys()){
            if (vertex == v){vInGraph = true;}
        }
        if (vInGraph){
            Dictionary<V,W> value = graph.valueOf(v);
            Set<Tuple2<V,W>> sucs = new HashSet<>();
            for (Tuple2<V,W> tuple : value.keysValues()){
                sucs.insert(tuple);
            }
            return sucs;
        } else {
            throw new GraphException("No existe el vertice en el grafo");
        }

    }


    public Set<WeightedEdge<V, W>> edges() {
        /*
        - Recorrer los keysValues del diccionario
        - Creo una arista
        - Comprobar que dicha arista no haya sido añadida al conjunto
        - En caso de ser falso, añadir la arista al conjunto
         */

        Set<WeightedEdge<V,W>> edges = new HashSet<>();
        for (Tuple2<V, Dictionary<V,W>> kv : graph.keysValues()){
            V vertex = kv._1();
            Dictionary<V,W> dstWeight = kv._2();

            //Crear todas las aristas para un vertice
            for (Tuple2<V,W> tuple : dstWeight.keysValues()){
                WeightedEdge<V,W> newEdge = new WE<>(vertex, tuple._1(), tuple._2());

                //Comprobar que este vertice no esta en la lista
                boolean esta = false;
                for (WeightedEdge<V,W> we : edges){
                    if (we.hashCode() == newEdge.hashCode()){
                        esta = true;
                    }
                }
                if (!esta){
                    edges.insert(newEdge);
                }
            }
        }
        return edges;
    }






    /** DON'T EDIT ANYTHING BELOW THIS COMMENT **/


    public Set<V> vertices() {
        Set<V> vs = new HashSet<>();
        for (V v : graph.keys())
            vs.insert(v);
        return vs;
    }


    public boolean isEmpty() {
        return graph.isEmpty();
    }

    public int numVertices() {
        return graph.size();
    }


    public int numEdges() {
        int num = 0;
        for (Dictionary<V, W> d : graph.values())
            num += d.size();
        return num / 2;
    }


    public String toString() {
        String className = getClass().getSimpleName();
        String s = className + "(vertices=(";

        Iterator<V> it1 = vertices().iterator();
        while (it1.hasNext())
            s += it1.next() + (it1.hasNext() ? ", " : "");
        s += ")";

        s += ", edges=(";
        Iterator<WeightedEdge<V, W>> it2 = edges().iterator();
        while (it2.hasNext())
            s += it2.next() + (it2.hasNext() ? ", " : "");
        s += "))";

        return s;
    }
}
