package dataStructures.dictionary;
import dataStructures.list.LinkedList;
import dataStructures.list.List;

import dataStructures.list.ArrayList;
import dataStructures.set.AVLSet;
import dataStructures.set.Set;
import dataStructures.tuple.Tuple2;

/**
 * Estructuras de Datos. Grados en Informatica. UMA.
 * Examen de septiembre de 2018.
 *
 * Apellidos, Nombre:
 * Titulacion, Grupo:
 */
public class HashBiDictionary<K,V> implements BiDictionary<K,V>{
	private Dictionary<K,V> bKeys;
	private Dictionary<V,K> bValues;

	public HashBiDictionary() {
		bKeys = new HashDictionary<>();
		bValues = new HashDictionary<>();
	}

	public boolean isEmpty() {
		return bKeys.isEmpty() || bValues.isEmpty();
	}

	public int size() {
		if (bKeys.size() != bValues.size()){
			throw new RuntimeException("Los diccionarios no estan bien formados");
		}
		return bKeys.size();
	}

	public void insert(K k, V v) {
		boolean esta = false;
		for (K key : bKeys.keys()){
			if (key == k){
				V value = bKeys.valueOf(key);
				esta = true;
				bKeys.insert(k,v);
				bValues.delete(value);
				bValues.insert(v,k);
			}
		}
		if (!esta){
			bKeys.insert(k,v);
			bValues.insert(v,k);
		}
	}

	public V valueOf(K k) {
		for (K key : bKeys.keys()) {
			if (key == k) {
				return bKeys.valueOf(k);
			}
		}
		return null;
	}

	public K keyOf(V v) {
		for (V values : bValues.keys()){
			if (v == values){ return bValues.valueOf(v); }
		}
		return null;
	}

	public boolean isDefinedKeyAt(K k) {
		return bKeys.isDefinedAt(k);
	}

	public boolean isDefinedValueAt(V v) {
		return bValues.isDefinedAt(v);
	}

	public void deleteByKey(K k) {
		if(isDefinedKeyAt(k)){
			bValues.delete(bKeys.valueOf(k));
			bKeys.delete(k);
		}
	}

	public void deleteByValue(V v) {
		if(isDefinedValueAt(v)){
			bKeys.delete(bValues.valueOf(v));
			bValues.delete(v);
		}
	}

	public Iterable<K> keys() {
		return bKeys.keys();
	}

	public Iterable<V> values() {
		return bValues.keys();
	}

	public Iterable<Tuple2<K, V>> keysValues() {
		return bKeys.keysValues();
	}


	public static <K,V extends Comparable<? super V>> BiDictionary<K, V> toBiDictionary(Dictionary<K,V> dict) {
		// 1. Comprobar que el diccionario es inyectivo
		// Para saber si es inyectivo sacamos dos conjuntos con las claves y los valores y si difieren en tamaño entonces no puede ser
		// inyectivo
		Set<V> value = new AVLSet<>();
		for (V v : dict.values()){
			value.insert(v);
		}
		List<K> claves = new LinkedList<>();
		for (K key : dict.keys()){
			boolean esta = false;
			for (int i = 0; i < claves.size() && !esta; i++){
				if (key == claves.get(i)) {
					esta = true;
				}
			}
			if (!esta){
				claves.append(key);
			}
		}

		if (value.size() != claves.size()){
			throw new IllegalArgumentException();
		}

		BiDictionary<K,V> sol = new HashBiDictionary<>();
		for (Tuple2<K,V> tupla : dict.keysValues()){
			sol.insert(tupla._1(), tupla._2());
		}
		return sol;
	}

	public <W> BiDictionary<K, W> compose(BiDictionary<V,W> bdic) {
		BiDictionary<K,W> sol = new HashBiDictionary<>();
		for (V key_bdic : bdic.keys()){
			if (this.isDefinedValueAt(key_bdic)){
				sol.insert(this.keyOf(key_bdic),bdic.valueOf(key_bdic));
			}
		}
		return sol;
	}

	public static <K extends Comparable<? super K>> boolean isPermutation(BiDictionary<K,K> bd) {
		Set<K> claves = new AVLSet<>();
		Set<K> valores = new AVLSet<>();
		for (Tuple2<K,K> tupla : bd.keysValues()){
			claves.insert(tupla._1());
			valores.insert(tupla._2());
		}
		boolean sol = true;
		for (K elem : claves){
			if (!valores.isElem(elem)){
				sol = false;
			}
		}
		return sol;
	}

	// Solo alumnos con evaluaci�n por examen final.
	// =====================================

	public static <K extends Comparable<? super K>> List<K> orbitOf(K k, BiDictionary<K,K> bd) {
		// TODO
		return null;
	}

	public static <K extends Comparable<? super K>> List<List<K>> cyclesOf(BiDictionary<K,K> bd) {
		// TODO
		return null;
	}

	// =====================================


	@Override
	public String toString() {
		return "HashBiDictionary [bKeys=" + bKeys + ", bValues=" + bValues + "]";
	}


}
