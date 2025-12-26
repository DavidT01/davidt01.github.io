module Niske where

import Data.List as List (sortBy)
import Data.Char

comp :: (Int, String) -> (Int, String) -> Ordering
comp (d1, _) (d2, _)
    | d1 <= d2 = GT
    | d1 > d2 = LT

najduza :: [String] -> String
najduza lst = snd $ head $ sortBy (comp) $ map (\s -> (length s, s)) lst

umanji :: String -> String
umanji str = map (\c -> if c >= 'A' && c <= 'Z' then toLower(c) else c) str

razdvoj :: Char -> String -> [String]
razdvoj sep str = [uzmi] ++ razdvoj sep (drop (length uzmi + 1) str)
    where uzmi = takeWhile (/= sep) str

spoj :: String -> [String] -> String
spoj _ [a] = a
spoj sep (h:t) = h ++ sep ++ (spoj sep t)

data Poklapanje = MkPoklapanje { kar :: Char, poz :: Int}

poklapanjeShow :: Poklapanje -> String
poklapanjeShow p = [kar p] ++ " (" ++ (show (poz p)) ++ ")"

instance Show Poklapanje where
    show = poklapanjeShow

poklapanjeM :: Int -> String -> Maybe Poklapanje
poklapanjeM i str
    | (length str) > i = Just (MkPoklapanje (str !! i) i)
    | otherwise = Nothing

poklapanjeE :: Int -> String -> Either String Poklapanje
poklapanjeE i str
    | (length str) > i = Right (MkPoklapanje (str !! i) i)
    | otherwise = Left "Index error"

pronadjiM :: Poklapanje -> String -> Maybe Bool
pronadjiM p str
    | (length str) > i && (str !! i) == k = Just True
    | (length str) > i = Just False
    | otherwise = Nothing
    where   k = kar p
            i = poz p

pronadjiE :: Poklapanje -> String -> Either String Bool
pronadjiE p str
    | (length str) > i && (str !! i) == k = Right True
    | (length str) > i = Right False
    | otherwise = Left "Index error"
    where   k = kar p
            i = poz p