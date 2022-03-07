-------------------------------------------------------------------------------
-- Ford-Fulkerson Algorithm. Maximal flow for a weighted directed graph.
--
-- Student's name:
-- Student's group:
--
-- Data Structures. Grado en Informática. UMA.
-------------------------------------------------------------------------------

module Feb2020.DataStructures.Graph.FordFulkerson where

import Data.List  ((\\))
import Feb2020.DataStructures.Graph.WeightedDiGraph
import Feb2020.DataStructures.Graph.WeightedDiGraphBFT

{-
Inicialmente se crea una lista de arcos vacía para representar la solución.
Mientras haya un camino (path) de S a T en G:
    Se calcula el flujo máximo (mf) de dicho camino (path).
    Para cada arco del grafo G que forme parte del camino (path), se decrementa su peso en mf unidades.
    Para cada arco del grafo G que forme parte del camino contrario a path, se incrementa su peso en mf unidades.
    A la lista solución se le añade el flujo de los arcos del camino (path) pero con peso mf.
La lista solución contendrá los arcos que forman el grafo con flujo máximo.
La suma de los pesos de los arcos de la solución que salen de S será el flujo máximo de la red.
-}

--Flujo maximo de un camino
maxFlowPath :: Path (WDiEdge a Integer) -> Integer
maxFlowPath path = minimum (map getWeight path)

--Devuelve el peso 
getWeight :: WDiEdge a Integer -> Integer
getWeight (E x w y) = w

--Devuelve el inicio
getX :: WDiEdge a Integer -> a
getX (E x w y) = x

--Devuelve el extremo
getY :: WDiEdge a Integer -> a
getY (E x w y) = y

--Actualiza o añade una arista al grafo con un peso w
updateEdge ::(Eq a) => a -> a -> Integer -> [WDiEdge a Integer] -> [WDiEdge a Integer]
updateEdge x y w [] = [E x w y]
updateEdge x y w edges 
    | getX (head edges) == x && getY (head edges) == y = (updateWeight (head edges)) ++ (tail edges)
    | otherwise = (head edges) : updateEdge x y w (tail edges)
        where 
            updateWeight (E x p y) 
                | (w + p) > 0 = [(E x (w + p) y)]
                | otherwise = []
            
--Actualiza los arcos de un camino con un peso p            
updateEdges :: (Eq a) => Path (WDiEdge a Integer) -> Integer -> [WDiEdge a Integer] -> [WDiEdge a Integer]
updateEdges [] p edges = edges 
updateEdges path p [] = path
updateEdges (x:xs) p edges = updateEdges xs p (updateEdge (getX x) (getY x) p edges)

--Crea una nueva lista con los arcos pero procesado de forma diferente
addFlow :: (Eq a) => a -> a -> Integer -> [WDiEdge a Integer] -> [WDiEdge a Integer]
addFlow x y p [] = [(E x p y)]
addFlow x y p sol 
    | getX (head sol) == x && getY (head sol) == y = (E x ((getWeight (head sol)) + p) y) : (tail sol)
    | getX (head sol) == y && getY (head sol) == x && getWeight (head sol) == p = tail sol
    | getX (head sol) == y && getY (head sol) == x && getWeight (head sol) < p = (E y (p - (getWeight (head sol))) x) : (tail sol)
    | getX (head sol) == y && getY (head sol) == x && getWeight (head sol) > p = (E y ((getWeight (head sol)) - p) x) : (tail sol)
    | otherwise = (head sol) : addFlow x y p (tail sol)

--Aplica addFlow a un camino 
addFlows :: (Eq a) => Path (WDiEdge a Integer) -> Integer -> [WDiEdge a Integer] -> [WDiEdge a Integer]
addFlows [] p sol =  sol 
addFlows path p [] = path
addFlows (x:xs) p sol = addFlows xs p (addFlow (getX x) (getY x) p sol) 

fordFulkerson :: (Ord a) => (WeightedDiGraph a Integer) -> a -> a -> [WDiEdge a Integer]
fordFulkerson wg src dst = faux wg src dst [] (bftPathTo wg src dst)  --funcion auxiliar que incluye la lista solucion y el path
    where
        faux _ _ _ sol Nothing = sol
        faux wg src dist sol (Just path) = faux wdg src dist solAct (bftPathTo wdg src dist)
            where
                mf = maxFlowPath path
                edges = updateEdges (reversePath path) mf (updateEdges path (-mf) (weightedDiEdges wg))
                wdg = mkWeightedDiGraphEdges (vertices wg) edges
                solAct = addFlows path mf sol

reversePath :: Path (WDiEdge a Integer) -> Path (WDiEdge a Integer) 
reversePath [] = []
reversePath (x:xs) = reversePath xs ++ [(E (getY x) (getWeight x) (getX x))] 
                     
                        


maxFlow :: (Ord a) => [WDiEdge a Integer] -> a -> Integer
maxFlow edges src = sumWeights (filter (\(E x _ _) -> x == src) edges)
    where
        sumWeights [] = 0
        sumWeights (x:xs) = getWeight x + sumWeights xs

maxFlowMinCut :: (Ord a) => (WeightedDiGraph a Integer) -> a -> a -> [a] -> Integer
maxFlowMinCut = undefined

-- A partir de aquí hasta el final
-- SOLO para alumnos a tiempo parcial 
-- sin evaluación continua

localEquilibrium :: (Ord a) => WeightedDiGraph a Integer -> a -> a -> Bool
localEquilibrium = undefined

sourcesAndSinks :: (Eq a) => WeightedDiGraph a b -> ([a],[a])
sourcesAndSinks = undefined

unifySourceAndSink :: (Eq a) => WeightedDiGraph a Integer -> a -> a -> WeightedDiGraph a Integer
unifySourceAndSink = undefined
