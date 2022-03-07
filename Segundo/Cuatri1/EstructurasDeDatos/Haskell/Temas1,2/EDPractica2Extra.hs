-------------------------------------------------------------------------------
-- Estructuras de Datos. 2º ETSI Informática. UMA
-- Práctica 2 - Ejercicios extra
--
-- Alumno: CANO MORENO, FRANCISCO JAVIER
-------------------------------------------------------------------------------

module Practica2Extra where

import           Data.Char
import           Test.QuickCheck
import           Text.Show.Functions


----------------------------------------------------------------------
-- Ejercicio - empareja
----------------------------------------------------------------------

empareja :: [a] -> [b] -> [(a, b)]
empareja [] [] = []
empareja (x:xs) [] =  []
empareja [] (y: ys) =   []
empareja (x:xs) (y:ys)=  (x, y) : empareja xs ys

prop_empareja_OK :: (Eq b, Eq a) => [a] -> [b] -> Bool
prop_empareja_OK xs ys = zip xs ys == empareja xs ys


----------------------------------------------------------------------
-- Ejercicio - emparejaCon
----------------------------------------------------------------------

emparejaCon ::  (a -> b -> c) -> [a] -> [b] -> [c]
emparejaCon f _ [] = []
emparejaCon f [] _ = []
emparejaCon f (x:xs) (y:ys) = (f x y) : emparejaCon f xs ys


prop_emparejaCon_OK :: Eq c => (a -> b -> c) -> [a] -> [b] -> Bool
prop_emparejaCon_OK f xs ys = emparejaCon f xs ys == zipWith f xs ys

----------------------------------------------------------------------
-- Ejercicio - separa
----------------------------------------------------------------------

separaRec :: (a -> Bool) -> [a] -> ([a], [a])
separaRec f xs = separaAc f xs ([], [])
    where
        separaAc f [] ac = ac
        separaAc f (x:xs) (ys, hs) 
            | f x == True = separaAc f xs (ys ++ [x], hs)
            | otherwise = separaAc f xs (ys, hs ++ [x]) 

separaC :: (a -> Bool) -> [a] -> ([a], [a])
separaC f xs = ([x | x <- xs, f x == True], [x | x <- xs, f x /= True]) 

separaP :: (a -> Bool) -> [a] -> ([a], [a])
separaP f xs = undefined

 


prop_separa_OK :: Eq a => (a -> Bool) -> [a] -> Bool
prop_separa_OK f xs = separaRec f xs == separaC f xs

----------------------------------------------------------------------
-- Ejercicio - lista de pares
----------------------------------------------------------------------

cotizacion :: [(String, Double)]
cotizacion = [("apple", 116), ("intel", 35), ("google", 824), ("nvidia", 67)]

buscarRec :: Eq a => a -> [(a,b)] -> [b]
buscarRec _ [] = []
buscarRec x ((k, v):xs)  
    | x == k = [v]
    | otherwise = buscarRec x xs

buscarC :: Eq a => a -> [(a, b)] -> [b]
buscarC x xs = [ v | (k, v) <- xs, x == k]

buscarP :: Eq a => a -> [(a, b)] -> [b]
buscarP x lt = undefined

prop_buscar_OK :: (Eq a, Eq b) => a -> [(a, b)] -> Bool
prop_buscar_OK x lt = buscarRec x lt == buscarC x lt 

{-

Responde las siguientes preguntas si falla la propiedad anterior.

¿Por qué falla la propiedad prop_buscar_OK?

Realiza las modificaciones necesarias para que se verifique la propiedad.

-}

valorCartera :: [(String, Double)] -> [(String, Double)] -> Double
valorCartera xs ys = sum  (zipWith (*) valor_cotizacion cantidad)
    where
        valor_cotizacion = map (\ [x] -> x) (map (\ k -> buscarC k ys) (map (\ (k, v) -> k) lista_filtro))
            where 
                lista_filtro = filter (\ (k, v) -> k `elem` ( map (\ (k, v) -> k) ys)) xs
        cantidad = map (\ (k, v) -> v) modificada
            where
                modificada = filter (\ (k, v) -> k `elem` ( map (\ (k, v) -> k) ys)) xs
----------------------------------------------------------------------
-- Ejercicio - mezcla
----------------------------------------------------------------------

mezcla :: Ord a => [a] -> [a] -> [a]
mezcla [] [] = []
mezcla [] xs = xs
mezcla ys [] = ys
mezcla (x:xs) (y:ys) 
    | x > y = y : mezcla (x:xs) ys
    | otherwise = x : mezcla xs (y:ys)
----------------------------------------------------------------------
-- Ejercicio - takeUntil
----------------------------------------------------------------------

takeUntil :: (a -> Bool) -> [a] -> [a]
takeUntil f [] = []
takeUntil f (x:xs)
    | f x == True = []
    | otherwise = x : takeUntil f xs 
prop_takeUntilOK :: Eq a => (a -> Bool) -> [a] -> Bool
prop_takeUntilOK f xs = takeWhile f xs == takeUntil f xs

----------------------------------------------------------------------
-- Ejercicio - número feliz
----------------------------------------------------------------------

digitosDe :: Integer -> [Integer]
digitosDe 0 = [0]
digitosDe 1 = [1]
digitosDe 2 = [2]
digitosDe 3 = [3]
digitosDe 4 = [4]
digitosDe 5 = [5]
digitosDe 6 = [6]
digitosDe 7 = [7]
digitosDe 8 = [8]
digitosDe 9 = [9]
digitosDe x = digitosDe (div x 10) ++ [mod x 10]

sumaCuadradosDigitos :: Integer -> Integer
sumaCuadradosDigitos v = (sum.map (\ x -> x * x).digitosDe) v

esFeliz :: Integer -> Bool
esFeliz x = esFelizAc x []
    where 
        esFelizAc 1 ac = True 
        esFelizAc x ac 
            | x `notElem` ac = esFelizAc (sumaCuadradosDigitos x) (x:ac) 
            | otherwise = False 

felicesHasta :: Integer -> [Integer]
felicesHasta x = filter esFeliz [1..x]  

{-

Responde a la siguiente pregunta.

¿Cuántos números felices hay menores o iguales que 1000? -> 143

-}

----------------------------------------------------------------------
-- Ejercicio - borrar
----------------------------------------------------------------------

borrarRec :: Eq a => a -> [a] -> [a]
borrarRec x [] = []
borrarRec x (y:xs)
    | x == y = borrarRec x xs
    | otherwise = y : borrarRec x xs

borrarC :: Eq a => a -> [a] -> [a]
borrarC x xs = [ y | y <-  xs, y /= x] 

borrarP :: Eq a => a -> [a] -> [a]
borrarP x xs = foldr f [] xs
    where
        f cabeza solCola
            | x == cabeza = solCola
            | otherwise = cabeza : solCola


prop_borrar_OK :: Eq a => a -> [a] -> Bool
prop_borrar_OK x xs = borrarRec x xs == borrarC x xs && borrarC x xs == borrarP x xs

----------------------------------------------------------------------
-- Ejercicio - agrupar
----------------------------------------------------------------------

agrupar :: Eq a => [a] -> [[a]]
agrupar [] = []


----------------------------------------------------------------------
-- Ejercicio - aplica
----------------------------------------------------------------------

aplicaRec :: a -> [ a -> b] -> [b]
aplicaRec _ [] = []
aplicaRec x (y:ys) = y x : aplicaRec x ys

aplicaC :: a -> [ a -> b] -> [b]
aplicaC x xs = [ h x | h <- xs]

aplicaP :: a -> [ a -> b] -> [b]
aplicaP x xs = foldr f [] xs
    where 
        f cabeza solCola = cabeza x : solCola

aplicaM :: a -> [ a -> b] -> [b]
aplicaM x xs = map (\ f -> f x) xs

prop_aplica_OK :: Eq b => a -> [a -> b] -> Bool
prop_aplica_OK x xs = aplicaC x xs == aplicaM x xs && aplicaP x xs == aplicaRec x xs && aplicaC x xs == aplicaP x xs
