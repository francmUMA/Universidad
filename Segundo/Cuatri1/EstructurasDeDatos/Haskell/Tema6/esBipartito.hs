import DataStructures.Graph.Graph
import DataStructures.Stack.LinearStack as S 
import DataStructures.Set.LinearSet as Set

data Color = Rojo | Azul deriving (Eq, Show, Ord)
compatible Rojo = Azul
compatible Azul = Rojo

esBipartito :: Graph a -> Bool
esBipartito g = faux Set.empty (S.push (head (vertices g), Rojo) S.empty)
    where 
        faux visitedColor stack
            | S.isEmpty stack = True
            | otherwise = undefined