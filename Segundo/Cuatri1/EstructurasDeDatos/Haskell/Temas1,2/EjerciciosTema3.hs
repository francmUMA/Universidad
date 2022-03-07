
{-
module QueueP(QueueP,
             isEmpty,
             empty,
             enqueue,
             first,
             dequeue
             ) where

import           Test.QuickCheck
-}

{-module Set (Set,
            isEmpty,
            insert,
            delete,
            isElem,
            empty
            ) where
import Test.QuickCheck
-}
--import DataStructures.Stack.LinearStack 
{-
data Set a  = St [a]
    deriving (Show)
-}
{-

data Set a = Empty
           | Node a (Set a)
           deriving (Show, Eq)

-}


{-
    Ejercicio 1 --- Cadena equilibrada


wellBalanced :: String -> Bool
wellBalanced xs = wellBalanced' xs empty

wellBalanced' ::String -> Stack Char -> Bool
wellBalanced' [] s = isEmpty s
wellBalanced' (x:xs) s 
    | x == '{' || x == '(' || x == '[' = wellBalanced' xs (push x s)
    | x == '}' && top s == '{' = wellBalanced' xs (pop s)
    | x == ')' && top s == '(' = wellBalanced' xs (pop s)
    | x == ']' && top s == '[' = wellBalanced' xs (pop s)
    | otherwise = wellBalanced' xs s 

-}

    {-
        Ejercicio 4 --- Notacion Infija
    -}

{-
    Ejercicio 8 --- Cola de Prioridades

cola :: QueueP Int
cola = Node 1 (Node 2 (Node 5 (Node 8 Empty)))

empty :: QueueP a
empty = Empty

isEmpty :: QueueP a -> Bool
isEmpty Empty = True
isEmpty _ = False

enqueue :: (Ord a) => a -> QueueP a -> QueueP a
enqueue x Empty = Node x Empty
enqueue x (Node y q)
    | x > y =  Node y (enqueue x q)
    | otherwise = Node x (Node y q)

dequeue :: QueueP a -> QueueP a
dequeue Empty = error "La cola esta vacia"
dequeue (Node x q) = q 

first :: QueueP a -> a
first Empty =  error "La cola esta vacia"
first (Node x q) = x 
-}

{-
    Ejercicio 9a --- Set con nodos enlazados


sample2 :: Set Char
sample2 = Node 'a' (Node 'c' (Node 'f' (Node 'z' Empty)))

sample3 :: Set Char
sample3 = Node 'b' (Node 'd' (Node 'f' (Node 'g' Empty)))

isEmpty :: Set a -> Bool
isEmpty Empty = True
isEmpty _ = False

insert :: Eq a => a -> Set a -> Set a
insert x Empty = Node x Empty
insert x (Node y s)
    | x == y = Node y s
    | otherwise = Node y (insert x s)

delete :: Eq a => a -> Set a -> Set a
delete x Empty = error "El conjunto esta vacio"
delete x (Node y s)
    | x == y = s
    | otherwise = Node y (delete x s)

isElem :: Ord a => a -> Set a -> Bool
isElem _ Empty = False
isElem x (Node y s)
    | x == y = True
    | y > x = False
    | otherwise = isElem x s

empty :: Set a
empty = Empty

union :: Ord a => Set a -> Set a -> Set a
union Empty Empty = Empty
union s Empty = s
union Empty q = q
union (Node y s1) (Node x s2)
    | x == y = Node y (union s1 s2)
    | x < y = Node x (union (Node y s1) s2)
    | otherwise = Node y (union s1 (Node x s2))


intersection :: Ord a => Set a -> Set a -> Set a
intersection _ Empty = Empty
intersection Empty _ = Empty
intersection (Node x s1) s2
    | isElem x s2  = Node x (intersection s1 s2 )
    | otherwise = intersection  s1 s2

difference :: Ord a => Set a -> Set a -> Set a
difference Empty Empty = Empty
difference s1 Empty = s1
difference Empty s2 = Empty
difference (Node x s) s2 
    | isElem x s2  = difference s s2
    | otherwise = Node x (difference s s2)

isSubset :: Ord a => Set a -> Set a -> Bool
isSubset Empty Empty = True
isSubset Empty _ = True 
isSubset _ Empty = False
isSubset (Node x s1) s2 
    | isElem x s2 = isSubset s1 s2 
    | otherwise = False

-}

{-
    Ejercicio 9b --- Set con listas


sample2 :: Set Char
sample2 = St ['a', 'c', 'f', 'z']

isEmpty :: Set a -> Bool
isEmpty (St []) = True
isEmpty _ = False

insert :: Eq a => a -> Set a -> Set a
insert x (St []) = St [x]
insert x (St (y:xs))
    | x == y = St (y:xs)
    | otherwise = undefined

delete :: Eq a => a -> Set a -> Set a
delete x (St xs) = undefined


isElem :: Ord a => a -> Set a -> Bool
isElem _ (St []) = False
isElem x (St (y:xs))
    | x == y = True
    | y > x = False
    | otherwise = isElem x (St xs)

empty :: Set a
empty = St []
-}

{-
    Ejercicio 11 --- Bolsa

module Bag (Bag,
                        empty,
                        isEmpty,
                        insert,
                        occurrences,
                        delete
                        ) where
import Test.QuickCheck

data Bag a = Empty 
    | Node a Int (Bag a)
    deriving (Show)

sampleBag1 :: Bag Char 
sampleBag1 = Node 'a' 3 (Node 'b' 2 (Node 'c' 1 (Node 'g' 2 Empty)))

sampleBag2 :: Bag Char 
sampleBag2 = Node 'b' 3 (Node 'e' 2 (Node 'g' 2 (Node 'n' 2 Empty)))

empty :: Bag a
empty = Empty

isEmpty :: Bag a -> Bool
isEmpty Empty =  True 
isEmpty _ = False

insert :: (Ord a) => a -> Bag a -> Bag a
insert x Empty = Node x 1 Empty
insert x (Node y c b) 
    | x == y = Node x (c + 1) b
    | x > y = Node y c (insert x b)
    |otherwise = Node x 1 (Node y c b)

delete :: (Ord a) => a -> Bag a -> Bag a
delete _ Empty = Empty 
delete x (Node y c b) 
    | x == y = if c == 1 then b else Node y (c-1) b 
    | otherwise = Node y c (delete x b)

occurrences :: (Ord a) => a -> Bag a -> Int
occurrences _ Empty = 0
occurrences x (Node y c b) 
    | x == y = c 
    | otherwise = occurrences x b 

instance (Ord a, Arbitrary a) => Arbitrary (Bag a) where
 arbitrary = do
 xs <- listOf arbitrary
 return (foldr insert empty xs)

union :: Ord a => Bag a -> Bag a -> Bag a 
union b Empty = b
union Empty b = b 
union (Node x cx b1) (Node y cy b2)
    | x == y = Node x (cx + cy) (union b1 b2)
    | x < y = Node x cx (union b1 (Node y cy b2))
    | otherwise = Node y cy (union (Node x cx b1) b2)

intersection :: Ord a => Bag a -> Bag a -> Bag a
intersection _ Empty = Empty
intersection Empty _ = Empty
intersection (Node x cx b1) (Node y cy b2)
    | x == y = if cx > cy then Node y cy (intersection b1 b2) else Node x cx (intersection b1 b2)
    | x < y = intersection b1 (Node y cy b2)
    | otherwise = intersection (Node x cx b1) b2 
-}

{-
    Ejercicio 13 --- Plegado sobre Stack
-}

module FoldStackQueue where
import qualified DataStructures.Stack.LinearStack as S

foldrStack :: (a -> b -> b) -> b -> S.Stack a -> b
foldrStack f z s
 | S.isEmpty s = z
 | otherwise = S.top s `f` foldrStack f z (S.pop s)

listToStack :: [a] -> S.Stack a
listToStack xs = foldr S.push (S.empty) xs


 stackToList :: S.Stack a -> [a]
 stackToList s = foldrStack (:) [] s