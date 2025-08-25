module Karte where

import Data.List as List (sortBy)

comp :: (Int, Char) -> (Int, Char) -> Ordering
comp (v1, z1) (v2, z2)
            | v1 > v2 = GT
            | v1 < v2 = LT
            | z1 == 'T' && z2 /= 'T' = GT
            | z1 /= 'T' && z2 == 'T' = LT
            | z1 == 'P' && z2 /= 'P' = GT
            | z1 /= 'P' && z2 == 'P' = LT
            | z1 == 'K' && z2 /= 'K' = GT
            | z1 /= 'K' && z2 == 'K' = LT
            | z1 == 'H' && z2 /= 'H' = GT
            | z1 /= 'H' && z2 == 'H' = LT
            | otherwise = EQ

dodaj :: [(Int, Char)] -> (Int, Char) -> [(Int, Char)]
dodaj ruka karta =  if elem karta ruka then ruka
                    else sortBy (comp) $ karta : ruka

ukloni :: [(Int, Char)] -> (Int, Char) -> [(Int, Char)]
ukloni ruka karta = foldl azuriraj [] ruka
    where azuriraj acc ruka = if ruka == karta  then acc
                                                else acc ++ [ruka]

--ili

ukloni2 :: [(Int, Char)] -> (Int, Char) -> [(Int, Char)]
ukloni2 ruka karta = foldr azuriraj [] ruka
    where azuriraj ruka acc = if ruka == karta  then acc
                                                else ruka : acc

uporedi :: [(Int, Char)] -> [(Int, Char)] -> Ordering
uporedi ruka1 ruka2
    | (tail ruka1) == [] = comp (head ruka1) (head ruka2)
    | comp (head ruka1) (head ruka2) == LT = LT
    | comp (head ruka1) (head ruka2) == GT = GT
    | otherwise = uporedi (tail ruka1) (tail ruka2)

data Znak = Herc
            | Karo
            | Pik
            | Tref
            deriving Eq

instance Show Znak where
    show Herc = "H"
    show Karo = "K"
    show Pik = "P"
    show Tref = "T"

data Karta = MkKarta { vrednost :: Int, znak :: Znak } deriving (Show, Eq)

type Ruka = [Karta]

izlistaj :: Znak -> Ruka -> [Karta]
izlistaj z ruka = filter (\k -> (znak k) == z) ruka

comp2 :: Karta -> Karta -> Ordering
comp2 k1 k2 = comp (vrednost k1, head (show (znak k1))) (vrednost k2, head (show (znak k2)))

dodaj2 :: Ruka -> Karta -> Ruka
dodaj2 ruka karta = if elem karta ruka then ruka
                    else sortBy (comp2) $ karta : ruka

najjaca :: Ruka -> Karta
najjaca ruka = head $ sortBy (flip comp2) ruka