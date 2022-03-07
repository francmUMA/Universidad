-------------------------------------------------------------------------------
-- Apellidos, Nombre: 
-- Titulacion, Grupo: 
--
-- Estructuras de Datos. Grados en Informatica. UMA.
-------------------------------------------------------------------------------

module AVLBiDictionary( BiDictionary
                      , empty
                      , isEmpty
                      , size
                      , insert
                      , valueOf
                      , keyOf
                      , deleteByKey
                      , deleteByValue
                      , toBiDictionary
                      , compose
                      , isPermutation
                      , orbitOf
                      , cyclesOf
                      ) where

import qualified DataStructures.Dictionary.AVLDictionary as D
import qualified DataStructures.Set.BSTSet               as S

import           Data.List                               (intercalate, nub,
                                                          (\\))
import           Data.Maybe                              (fromJust, fromMaybe,
                                                          isJust)
import           Test.QuickCheck


data BiDictionary a b = Bi (D.Dictionary a b) (D.Dictionary b a)

-- | Exercise a. empty, isEmpty, size

empty :: (Ord a, Ord b) => BiDictionary a b
empty = Bi D.empty D.empty

isEmpty :: (Ord a, Ord b) => BiDictionary a b -> Bool
isEmpty (Bi dictvk dictkv) = D.isEmpty dictvk || D.isEmpty dictkv

size :: (Ord a, Ord b) => BiDictionary a b -> Int
size (Bi dictkv dictvk) = D.size dictvk

-- | Exercise b. insert

insert :: (Ord a, Ord b) => a -> b -> BiDictionary a b -> BiDictionary a b
--No se puede dar el caso en el que haya tamaños dispares
insert key value (Bi dictkv dictvk) = aux (D.keys dictkv) (D.values dictkv)
  where
    aux [] _ = Bi (D.insert key value dictkv) (D.insert value key dictvk)
    aux (k:ks) (v:vs)
      | k == key   = Bi (D.insert key value dictkv) (D.insert value key (D.delete v dictvk))
      | v == value = Bi (D.insert key value (D.delete k dictkv)) (D.insert value key dictvk)
      | otherwise  = aux ks vs

-- | Exercise c. valueOf

valueOf :: (Ord a, Ord b) => a -> BiDictionary a b -> Maybe b
valueOf k (Bi dictkv dictvk) = D.valueOf k dictkv

-- | Exercise d. keyOf

keyOf :: (Ord a, Ord b) => b -> BiDictionary a b -> Maybe a
keyOf v (Bi dictkv dictvk) = D.valueOf v dictvk

-- | Exercise e. deleteByKey

deleteByKey :: (Ord a, Ord b) => a -> BiDictionary a b -> BiDictionary a b
deleteByKey key (Bi dictkv dictvk) = aux (D.keys dictkv) (D.values dictkv)
  where
    aux [] _ = Bi dictkv dictvk
    aux (k:ks) (v:vs)
      | key == k  = Bi (D.delete k dictkv) (D.delete v dictvk)
      | otherwise = aux ks vs

-- | Exercise f. deleteByValue

deleteByValue :: (Ord a, Ord b) => b -> BiDictionary a b -> BiDictionary a b
deleteByValue value (Bi dictkv dictvk) = aux (D.keys dictkv) (D.values dictkv)
  where
    aux _ [] = Bi dictkv dictvk
    aux (k:ks) (v:vs)
      | value == v  = Bi (D.delete k dictkv) (D.delete v dictvk)
      | otherwise = aux ks vs

-- | Exercise g. toBiDictionary

toBiDictionary :: (Ord a, Ord b) => D.Dictionary a b -> BiDictionary a b
toBiDictionary dic
  | inyectivo dic = aux (D.keysValues dic) (Bi D.empty D.empty)
  | otherwise     = error "El diccionario no es inyectivo"
    where
      aux [] dicSol       = dicSol
      aux (kv:kvs) dicSol = aux kvs (uncurry insert kv dicSol)

inyectivo :: (Ord a, Ord b) => D.Dictionary a b -> Bool
inyectivo dic = length (D.keys dic) == length (D.values dic)


-- | Exercise h. compose

compose :: (Ord a, Ord b, Ord c) => BiDictionary a b -> BiDictionary b c -> BiDictionary a c
compose = undefined

-- | Exercise i. isPermutation

isPermutation :: Ord a => BiDictionary a a -> Bool
isPermutation = undefined



-- |------------------------------------------------------------------------


-- | Exercise j. orbitOf

orbitOf :: Ord a => a -> BiDictionary a a -> [a]
orbitOf = undefined

-- | Exercise k. cyclesOf

cyclesOf :: Ord a => BiDictionary a a -> [[a]]
cyclesOf = undefined

-- |------------------------------------------------------------------------


instance (Show a, Show b) => Show (BiDictionary a b) where
  show (Bi dk dv)  = "BiDictionary(" ++ intercalate "," (aux (D.keysValues dk)) ++ ")"
                        ++ "(" ++ intercalate "," (aux (D.keysValues dv)) ++ ")"
   where
    aux kvs  = map (\(k,v) -> show k ++ "->" ++ show v) kvs
