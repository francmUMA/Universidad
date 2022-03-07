----------------------------------------------
-- Estructuras de Datos.  2018/19
-- 2º Curso del Grado en Ingeniería [Informática | del Software | de Computadores].
-- Escuela Técnica Superior de Ingeniería en Informática. UMA
--
-- Examen 4 de febrero de 2019
--
-- ALUMNO/NAME:
-- GRADO/STUDIES:
-- NÚM. MÁQUINA/MACHINE NUMBER:
--
----------------------------------------------

module Feb2019.Kruskal(kruskal) where

import qualified Feb2019.DataStructures.Dictionary.AVLDictionary as D
import qualified Feb2019.DataStructures.PriorityQueue.LinearPriorityQueue as Q
import Feb2019.DataStructures.Graph.DictionaryWeightedGraph

kruskal :: (Ord a, Ord w) => WeightedGraph a w -> [WeightedEdge a w]
kruskal g = undefined

--aux (PQedges g) [] (dicAsoc g)
{-
PQedges :: (Ord a, Ord w) => WeightedGraph a w -> PQueue (WeightedEdge a w) 
PQedges g = undefined
-}

