-------------------------------------------------------------------------------
-- Estructuras de Datos. 2º ETSI Informática. UMA
-- Práctica 2
--
-- Alumno: CANO MORENO, FRANCISCO JAVIER 
-------------------------------------------------------------------------------

module Practica2 where

import           Data.List
import           Test.QuickCheck

-------------------------------------------------------------------------------
-- Ejercicio 2 - máximoYResto
-------------------------------------------------------------------------------

máximoYRestoOrden :: Ord a => [a] -> (a,[a])
máximoYRestoOrden [] = error "La lista está vacía"
máximoYRestoOrden  xs = (m, borra m xs)
    where
        m = maximum xs

borra :: Ord a => a -> [a] -> [a]
borra _ [] = error "No está definido"
borra x (y:ys)
    | x == y = ys
    | otherwise = y:borra x ys

máximoYResto :: Ord a => [a] -> (a,[a])
máximoYResto [] = error "No está definido"
máximoYResto [x] = (x, [])
máximoYResto (x:xs)
    | x > n = (x, n:ys)
    | otherwise = (n, x:ys)
        where
            (n, ys) = máximoYResto xs


-------------------------------------------------------------------------------
-- Ejercicio 3 - reparte
-------------------------------------------------------------------------------

reparte :: [a] -> ([a], [a])
reparte  [] = ([],[])
reparte (x:y:rs) = (x:xs, y:ys)
    where
        (xs, ys) = reparte rs

-------------------------------------------------------------------------------
-- Ejercicio 4 - distintos
-------------------------------------------------------------------------------

distintos :: Eq a => [a] -> Bool
distintos [] = True 
distintos [x] = True
distintos (x:y:xs)
    | x == y = False
    | otherwise = distintos (y:xs)

-------------------------------------------------------------------------------
-- Ejercicio 13 - hoogle
-------------------------------------------------------------------------------

-- Hoogle (https://www.haskell.org/hoogle/) es un buscador para el API de Haskell.
-- Usa Hoogle para encontrar información sobre las funciones 'and', y 'zip'

desconocida :: Ord a => [a] -> Bool
desconocida xs = and [ x <= y | (x, y) <- zip xs (tail xs) ]

-------------------------------------------------------------------------------
-- Ejercicio 14 - inserta y ordena
-------------------------------------------------------------------------------

-- 14.a - usando takeWhile y dropWhile
inserta :: Ord a => a -> [a] -> [a]
inserta x xs = takeWhile (<x) xs ++ [x] ++ dropWhile (<x) xs

-- 14.b - mediante recursividad
insertaRec :: Ord a => a -> [a] -> [a]
insertaRec x [] = [x]
insertaRec x (y:ys)
    | x <= y = y:x:ys
    |otherwise = y : insertaRec x ys

-- 14.c

-- La línea de abajo no compila hasta que completes los apartados
-- anteriores.

-- p1_inserta x xs = desconocida xs ==> desconocida (inserta x xs)

-- 14.e - usando foldr
ordena :: Ord a => [a] -> [a]
ordena xs = foldr inserta [] xs


-- 14.f
prop_ordena_OK xs = desconocida (ordena xs) == True

-------------------------------------------------------------------------------
-- Ejercicio 21 - nub
-------------------------------------------------------------------------------

-- 21.a
nub' :: Eq a => [a] -> [a]
nub' [] = []
nub' [x] = [x]
nub' (x:y:ys)
    | x == y = nub' (y:ys)
    | otherwise = x:nub'(y:ys)

-- 21.b
p_nub' xs = nub xs == nub' xs

-- 21.c (distintos se define en el ejercicio 2)

p_sinRepes xs = distintos (nub' xs) == True 

{-

Escribe aquí tu razonamiento de por qué p_sinRepes no
es suficiente para comprobar que nub' es correcta:




-}

-- 21.d
todosEn :: Eq a => [a] -> [a] -> Bool
ys `todosEn` xs = all (`elem` xs) ys

p_sinReps' = undefined
