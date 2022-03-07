/**
 * @author Pepe Gallardo, Data Structures, Grado en Informática. UMA.
 *
 * Breadth First Traversal of a graph. Uses a FIFO store
 */

package graph;

import graph.Store;
import dataStructures.queue.ArrayQueue;

public class WeightedBreadthFirstTraversal<V,W> extends WTraversal<V,W> {

	public WeightedBreadthFirstTraversal(WTraversable<V,W> g, V source) {
		super(g,source);
	}
	
	private class FIFOStore<T> extends ArrayQueue<T> implements dataStructures.graph.Store<T> {

		public void insert(T elem) { enqueue(elem); }
		
		public T extract() { T elem = first(); dequeue(); return elem; }

	}
	
	public dataStructures.graph.Store<WDiEdge<V,W>> newStore() {
		return new FIFOStore<WDiEdge<V,W>>();
	}	

}
