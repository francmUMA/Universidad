-------------------------------------------------------------------------------
-- Estructuras de Datos. 2º Curso. ETSI Informática. UMA
--
-- (completa y sustituye los siguientes datos)
-- Titulación: Grado en Ingeniería …………………………………… [Informática | del Software | de Computadores].
-- Alumno: Cano Moreno, Francisco Javier
-- Fecha de entrega: DIA | Mes | AÑO
--
-- Relación de Ejercicios 1. Ejercicios resueltos: 1-17
--
-------------------------------------------------------------------------------
import Test.QuickCheck

--Ejercicio 1---
--Apartado  a---
cuadrado :: Integer -> Integer
cuadrado x = x * x
esTerna :: Integer -> Integer -> Integer -> Bool
esTerna x y z = cuadrado x + cuadrado y == cuadrado z

--Apartado  b---
terna :: Integer -> Integer -> (Integer, Integer, Integer)
terna x y 
    | x > y = (cuadrado x - cuadrado y, 2 * x * y, cuadrado x + cuadrado y)
    |otherwise = (cuadrado y - cuadrado x, 2 * x * y, cuadrado x + cuadrado y)

--Apartado  c---
p_ternas x y = x>0 && y>0 && x>y ==> esTerna l1 l2 h
    where 
        (l1,l2,h) = terna x y

--Ejercicio  2---   
intercambia :: (a, b) -> (b, a)
intercambia (x, y) = (y, x)

--Ejercicio  3---
--Apartado   a---
ordena2 :: Ord a => (a,a) -> (a,a)
ordena2 (x, y) 
    | x < y = (x, y)
    | x >= y = (y, x)

p1_ordena2 x y = enOrden (ordena2 (x,y))
    where enOrden (x,y) = x<=y

p2_ordena2 x y = mismosElementos (x,y) (ordena2 (x,y))
    where
        mismosElementos (x,y) (z,v) = (x==z && y==v) || (x==v && y==z)

--Apartado   b---
ordena3 :: Ord a => (a,a,a) -> (a,a,a)
ordena3 (x,y,z)
    |x < y && x < z && y < z = (x,y,z)
    |x < y && x < z && y > z = (x,z,y)
    |x > y && x < z && y < z = (y,x,z)
    |x > y && x > z && y < z = (y,z,x)
    |x > y && x > z && y > z = (z,y,x)
    |x < y && x > z && y > z = (z,x,y)

