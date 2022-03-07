import DataStructures.Graph.WeightedGraph
import DataStructures.Graph.GraphBFT
import DataStructures.Dictionary.AVLDictionary

g1 :: WeightedGraph Char Int
g1 =  mkWeightedGraphEdges ['a','b','c','d','e']
                           [ WE 'a' 3 'b', WE 'a' 7 'd'
                           , WE 'b' 4 'c', WE 'b' 2 'd'
                           , WE 'c' 5 'd', WE 'c' 6 'e'
                           , WE 'd' 5 'e'
                           ]

shortestPaths :: WeightedGraph Char Int -> Char -> [String]
shortestPaths wg src = faux (vertsNoSrc wg src) [src]  (insert src (0, [src]) empty)
    where
        faux [] _ dict         = map snd (values dict)
        faux nonUsed used dict = faux (remove vert nonUsed) (vert:used) (insert vert tuplePath dict)
            where
                vert = fst (selectPath wg src dict)
                tuplePath = snd (selectPath wg src dict)

remove :: Char -> [Char] -> [Char]
remove v l = [ x | x <- l, x /= v]

selectPath :: WeightedGraph Char Int -> Char -> Dictionary Char (Int, [Char]) -> (Char, (Int, [Char]))
selectPath wg src dict = undefined

vertsNoSrc :: WeightedGraph Char Int -> Char -> [Char]
vertsNoSrc wg src = [ v | v <- vertices wg, v /= src]
