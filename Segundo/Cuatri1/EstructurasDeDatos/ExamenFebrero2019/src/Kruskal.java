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

import dataStructures.graph.WeightedGraph;
import dataStructures.graph.WeightedGraph.WeightedEdge;

import dataStructures.dictionary.Dictionary;
import dataStructures.dictionary.HashDictionary;
import dataStructures.priorityQueue.PriorityQueue;
import dataStructures.priorityQueue.LinkedPriorityQueue;
import dataStructures.set.Set;
import dataStructures.set.HashSet;
import dataStructures.tuple.Tuple2;
import java.util.Iterator;

public class Kruskal {
	public static <V,W> Set<WeightedEdge<V,W>> kruskal(WeightedGraph<V,W> g) {
		Set<WeightedEdge<V,W>> sol = new HashSet<>();
		PriorityQueue<WeightedEdge<V,W>> PQedges = new LinkedPriorityQueue<>();
		Dictionary<V, Set<V>> vertJoins = new HashDictionary<>();

		/*
		1.Añadir aristas a la cola
		2.Añadir vertices al diccionario
		3.Crear Arbol minimo
			3.1 Recorrer la cola
			3.2 Ver si la arista une dos vertices desconectados
				3.2.1 Recorrer el diccionario viendo las uniones de cada vertice
				3.2.2 En caso de que no lo esten, actualizar diccionario y añadir la arista
		 */

		// 1. Añadir aristas a la cola
		for (WeightedEdge<V,W> edge : g.edges()){
			PQedges.enqueue(edge);
		}

		// 2. Añadir vertices al diccionario
		for (V vertex : g.vertices()){
			Set<V> uniones = new HashSet<>();
			uniones.insert(vertex);
			vertJoins.insert(vertex, uniones);
		}

		// 3. Recorrer la cola
		while (!PQedges.isEmpty()){
			WeightedEdge<V,W> analisisEdge = PQedges.first();
			/*
			- Para saber si la arista une vertices desconectados, basta con encontrar uno de los vertices y ver si el otro esta
			en su conjunto de union
			 */
			Iterator<Tuple2<V,Set<V>>> keyValue = vertJoins.keysValues().iterator();

			while (keyValue.hasNext()){
				Tuple2<V,Set<V>> tupla = keyValue.next();


				if (tupla._1() == analisisEdge.source()){

					if (!tupla._2().isElem(analisisEdge.destination())){
						tupla._2().insert(analisisEdge.destination());
						sol.insert(analisisEdge);
					}
				} else if (tupla._1() == analisisEdge.destination()){

					if (!tupla._2().isElem(analisisEdge.source())){
						tupla._2().insert(analisisEdge.source());
						sol.insert(analisisEdge);
					}
				}
			}
			PQedges.dequeue();
		}
		return sol;
	}

	// Sólo para evaluación continua / only for part time students
	public static <V,W> Set<Set<WeightedEdge<V,W>>> kruskals(WeightedGraph<V,W> g) {

		// COMPLETAR
		
		return null;
	}
}
