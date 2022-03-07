-------------------------------------------------------------------------------
-- Estructuras de Datos. Grado en Informática, IS e IC. UMA.
-- Examen de Febrero 2015.
--
-- Implementación del TAD Deque
--
-- Apellidos:
-- Nombre:
-- Grado en Ingeniería ...
-- Grupo:
-- Número de PC:
-------------------------------------------------------------------------------

module TwoListsDoubleEndedQueue
   ( DEQue
   , empty
   , isEmpty
   , first
   , last
   , addFirst
   , addLast
   , deleteFirst
   , deleteLast
   ) where

import Prelude hiding (last)
import Data.List(intercalate)
import Test.QuickCheck

data DEQue a = DEQ [a] [a]

-- Complexity:
empty :: DEQue a
empty = DEQ [] []

-- Complexity:
isEmpty :: DEQue a -> Bool
isEmpty (DEQ [] []) = True
isEmpty _ = False

-- Complexity:
addFirst :: a -> DEQue a -> DEQue a
addFirst x (DEQ a b) = DEQ (x:a) b

-- Complexity:
addLast :: a -> DEQue a -> DEQue a
addLast x (DEQ a b) = DEQ a (b ++ [x])

-- Complexity:
first :: DEQue a -> a
first (DEQ (f:fs) b) = f
first (DEQ [] b ) = first (DEQ (fst (splitAt (div (length b) 2) b)) () 

-- Complexity:
last :: DEQue a -> a
last (DEQ _ (l:ls)) = l

-- Complexity:
deleteFirst :: DEQue a -> DEQue a
deleteFirst (DEQ [] b) = DEQ [] b 
deleteFirst (DEQ (f:fs) b) = DEQ fs b

-- Complexity:
deleteLast :: DEQue a -> DEQue a
deleteLast (DEQ a (l:ls)) = DEQ a ls
deleteLast (DEQ a []) = DEQ a []


instance (Show a) => Show (DEQue a) where
   show q = "TwoListsDoubleEndedQueue(" ++ intercalate "," [show x | x <- toList q] ++ ")"

toList :: DEQue a -> [a]
toList (DEQ xs ys) =  xs ++ reverse ys

instance (Eq a) => Eq (DEQue a) where
   q == q' =  toList q == toList q'

instance (Arbitrary a) => Arbitrary (DEQue a) where
   arbitrary =  do
      xs <- listOf arbitrary
      ops <- listOf (oneof [return addFirst, return addLast])
      return (foldr id empty (zipWith ($) ops xs))
