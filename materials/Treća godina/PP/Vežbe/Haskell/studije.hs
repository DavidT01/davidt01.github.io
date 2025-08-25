module Studije where

-- StepenStudija je tip, može se praviti preko 3 različita konstruktora
data StepenStudija =  OsnovneStudije
                    | MasterStudije
                    | DoktorskeStudije
                    deriving (Show, Eq) -- podrazumevano instancira klase Show i Eq

-- tip koji koristi konstruktor Kratko i argument StepenStudija
data KratkiStepenStudija = Kratko StepenStudija

-- tip instancira Show i sada moramo implementirani show funkciju
instance Show KratkiStepenStudija where
    show (Kratko OsnovneStudije) = "BSc"
    show (Kratko MasterStudije) = "MSc"
    show (Kratko DoktorskeStudije) = "PhD"

-- tip instancira Eq, pa implementiramo poređenje
instance Eq KratkiStepenStudija where
    (==) (Kratko x) (Kratko y) = x == y

-- konstruktor prima 4 parametra
data Student = MkStudent {  indeks :: String,
                            ime :: String,
                            prezime :: String,
                            stepen :: StepenStudija }

formatStudent :: Student -> String
formatStudent s = (indeks s) ++ " : " ++ (ime s) ++ " " ++ (prezime s) ++ ", " ++ (show $ Kratko $ stepen s)

instance Show Student where
    show = formatStudent

instance Eq Student where
    (==) (MkStudent ind1 _ _ _) (MkStudent ind2 _ _ _) = ind1 == ind2

-- "Maybe a" tip se konstruiše sa konstruktorom "Nothing" ili "Just a"
type Rezultat = (Student, Maybe Int)

rezultati :: [Student] -> [Rezultat]
rezultati = map (\s -> (s, Nothing))

import Data.List as List (elemIndex, sortBy)
-- elemIndex vraća indeks pojavljivanja elementa ili Nothing ako se ne pojavljuje

-- "Either" znači da je ili jednog ili drugog tipa, tj. koriste se 2 konstruktora - "Left" i "Right"
poeni :: Student -> [Rezultat] -> Either String (Maybe Int)
poeni s rezultati =
    case mi of  Nothing -> Left ("Student sa indeksom " ++ (indeks s) ++ " ne postoji!")
                (Just i) -> Right (snd $ rezultati !! i)
    where mi = List.elemIndex s (map fst rezultati)
-- sa case lako pattern matchujemo funkcije

-- foldl znači da je acc levi argument i treba da dodajemo na kraj sa ++
ponisti :: Student -> [Rezultat] -> [Rezultat]
ponisti s rezultati = foldl azuriraj [] rezultati
    where azuriraj acc rez = if fst rez == s    then acc ++ [(s, Nothing)]
                                                else acc ++ [rez]

studije :: StepenStudija -> [Rezultat] -> [Rezultat]
studije ss = filter (\r -> ss == stepen (fst r))

polozeni :: [Rezultat] -> [Rezultat]
polozeni = filter (\(_, mp) -> poeni mp > 50)
    where   poeni Nothing = 0
            poeni (Just p) = p

-- foldr znači da je acc desni argument i treba da dodajemo na početak sa :
upisi :: Student -> Int -> [Rezultat] -> [Rezultat]
upisi s p rezultati =   if elem s studenti
                        then foldr azuriraj [] rezultati
                        else (s, Just p) : rezultati
    where   studenti = map fst rezultati
            azuriraj rez acc = if fst rez == s  then (s, Just p) : acc
                                                else rez : acc

najboljih :: Int -> [Rezultat] -> [Int]
najboljih k rez = take k
    $ sortBy (flip compare) -- sortira opadajuće jer smo obrnuli compare funkciju
    $ map (\(Just x) -> x)
    $ filter (/= Nothing)
    $ map snd rez