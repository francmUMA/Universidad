------------------------------------------------------------
-- Estructuras de Datos
-- Tema 3. Estructuras de Datos Lineales
-- Pablo López
--
-- Módulo del TAD Cola
------------------------------------------------------------

------------------------------------------------------------
-- Implementación del TAD Cola
------------------------------------------------------------

module Queue(Queue,
             isEmpty,
             empty,
             enqueue,
             first,
             dequeue
             ) where

import           Test.QuickCheck

{-
   Los constructores del TAD Cola son `empty` y `enqueue`. Podemos
   construir cualquier valor del TAD Cola con esas dos funciones. Por
   ejemplo:

          enqueue 5 (enqueue (7 enqueue (1 (enqueue 2 empty))))

   Ejercicio: En la cola anterior, ¿quién es el primero y quién es el
   último?
-}

{-
   Representaremos una cola en Haskell mediante el tipo algebraico
   `Queue`, que define los constructores de datos `Empty` y `Node`.
-}

data Queue a = Empty
             | Node a (Queue a)
             deriving (Eq, Show)

{-
   Para representar la cola:

          enqueue 5 (enqueue 7 enqueue (1 (enqueue 2 empty)))

   Podríamos usar internamente dos representaciones físicas:

          Node 5 (Node (7 Node (1 (Node 2 Empty))))

          Node 2 (Node (1 Node (7 (Node 5 Empty))))

   Observa que la diferencia está en el orden en que se disponen los
   elementos. Es una decisión que debe tomar el implementador del TAD.

   Ejercicio: ¿Cuál de estas representaciones es mejor? ¿Por qué?
-}

customers :: Queue String
customers = Node "peter" (Node "mary" (Node "john" Empty))

-- Complejidad: O(?)
-- |
-- >>> empty
-- Empty
empty :: Queue a
empty = undefined

-- Complejidad: O(?)
-- |
-- >>> isEmpty empty
-- True
-- >>> isEmpty customers
-- False
isEmpty :: Queue a -> Bool
isEmpty Empty = True 
isEmpty _ = False

-- Complejidad: O(?)
-- |
-- >>> first customers
-- "peter"
first :: Queue a -> a
first Empty = error "first sobre vacia"
first (Node x _) = x

-- Complejidad: O(?)
-- |
-- >>> dequeue customers
-- Node "mary" (Node "john" Empty)
-- >>> dequeue (dequeue customers)
-- Node "john" Empty
dequeue :: Queue a -> Queue a
dequeue Empty = error "dequeue sobre vacia"
dequeue (Node x q) = q 

-- Complejidad: O(n)
-- |
-- >>> enqueue "frank" customers
-- Node "peter" (Node "mary" (Node "john" (Node "frank" Empty)))
-- >>> enqueue "nicole" (enqueue "frank" customers)
-- Node "peter" (Node "mary" (Node "john" (Node "frank" (Node "nicole" Empty))))
enqueue :: a -> Queue a -> Queue a
enqueue x Empty = Node x Empty 
enqueue x (Node y q) = Node y (enqueue x q)

{-
   La siguiente instancia de `Arbitrary` es para enseñar a QuickCheck
   a generar `Queue` aleatorias: no hay que saber cómo hacerlo;
   siempre se facilita.
-}

instance Arbitrary a => Arbitrary (Queue a) where
  arbitrary =  do
                xs <- listOf arbitrary
                return (foldr enqueue empty xs)
