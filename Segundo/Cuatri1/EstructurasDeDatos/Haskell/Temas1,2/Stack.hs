------------------------------------------------------------
-- Estructuras de Datos
-- Tema 3. Estructuras de Datos Lineales
-- Pablo López
--
-- Módulo del TAD Stack
------------------------------------------------------------

------------------------------------------------------------
-- Implementación del TAD Stack
------------------------------------------------------------

module Stack where

import           Test.QuickCheck

data Stack a = Empty
             | Node a (Stack a)   -- Node es el constructor
             deriving (Show, Eq)

customers :: Stack String
--                 top
customers = Node "peter" (Node "mary" (Node "john" Empty))

-- Complejidad: O(?)
-- |
-- >>> empty
-- Empty
empty :: Stack a
empty = Empty

-- Complejidad: O(1)
-- |
-- | push "frank" customers
-- Node "frank" (Node "peter" (Node "mary" (Node "john" Empty)))
push :: a -> Stack a -> Stack a
push x p = Node x p                         --- p = Node c rs

-- Complejidad: O(1)
-- |
-- >>> pop customers
-- Node "mary" (Node "john" Empty)
pop :: Stack a -> Stack a
pop Empty = error "No se puede eliminar de una pila vacía"
pop (Node _ p) = p 

-- Complejidad: O(1)
-- |
-- >>> top customers
-- "peter"
top :: Stack a -> a
top Empty = error "Top sobre una lista vacía"
top (Node x p) =  x

-- Complejidad: O(1)
-- |
-- >>> isEmpty empty
-- True
--
-- isEmpty customers
-- False
isEmpty :: Stack a -> Bool
isEmpty  Empty = True 
isEmpty _ = False

-- esto es para enseñar a QuickCheck a generar Stack aleatorias:
-- no hay que saber cómo hacerlo; siempre se facilita

instance Arbitrary a => Arbitrary (Stack a) where
  arbitrary =  do
                xs <- listOf arbitrary
                return (foldr push empty xs)
