-- definicija biblioteke
module Tacka2D where

-- tip tačka
type Tacka = (Float, Float)

-- konstruktor za tačku
tacka :: Float -> Float -> Tacka
tacka x y = (x, y)

-- koordinantni početak
o :: Tacka
o = tacka 0.0 0.0

-- tip putanja (niz tačaka)
type Putanja = [Tacka]

-- konstruktor za putanju
putanja :: [Tacka] -> Putanja
putanja = id -- putanja lst = lst

-- dužina putanje
duzinaPutanje :: Putanja -> Int
duzinaPutanje = length -- putanja lst = length lst

-- translacija tačke
translirajTacku :: Tacka -> Float -> Float -> Tacka
translirajTacku tacka x y = (fst tacka + x, snd tacka + y)

-- rastojanje
rastojanje :: Tacka -> Tacka -> Float
rastojanje (x1, y1) (x2, y2) = sqrt $ (x1 - x2)^2 + (y1 - y2)^2

-- iz liste tačaka vraća one koje se nalaze u krugu poluprečnika r koji je u koord. početku
uKrugu :: Float -> [Tacka] -> [Tacka]
uKrugu r ts = [t | t <- ts, rastojanje t o < r]
--uKrugu r ts = filter (\t -> rastojanje t o < r) ts

-- translacija putanje
translirajPutanju :: Putanja -> Float -> Float -> Putanja
translirajPutanju p x y = map (\t -> translirajTacku t x y) p

-- nadovezivanje tačke na početak putanje
nadoveziP :: Tacka -> Putanja -> Putanja
nadoveziP = (:)

-- nadovezivanje tačke na kraj putanje
nadoveziK :: Tacka -> Putanja -> Putanja
nadoveziK t p = reverse $ nadoveziP t (reverse p)
-- nadoveziK t p = p ++ [t]

-- spajanje putanja
spoji :: Putanja -> Putanja -> Putanja
spoji = (++)

-- centroid (prosek po x, y)
centroid :: [Tacka] -> Tacka
centroid ts = tacka prosekX prosekY
    where prosekX = prosek $ map fst ts
          prosekY = prosek $ map snd ts
          prosek ts = (sum ts) / (fromIntegral $ length ts)

-- kvadrant tačke
kvadrantTacke :: Tacka -> Int
kvadrantTacke (x, y)
    | x > 0 && y > 0 = 1
    | x < 0 && y > 0 = 2
    | x < 0 && y < 0 = 3
    | x > 0 && y < 0 = 4
    | otherwise = 0

-- kvadrant putanje
kvadrantPutanje :: Putanja -> Int
kvadrantPutanje [] = 0
kvadrantPutanje p = if istiKvadrant then head kvadranti else 0
    where kvadranti = map kvadrantTacke p
          istiKvadrant = all (\k -> k == (head kvadranti)) (tail kvadranti)

-- tačke u kvadrantu
tackeUKvadrantu :: Int -> [Tacka] -> [Tacka]
tackeUKvadrantu k ts = filter (\t -> kvadrantTacke t == k) ts

-- tačke van kvadranta
tackeVanKvadranta :: Int -> [Tacka] -> [Tacka]
tackeVanKvadranta k ts = filter (\t -> kvadrantTacke t /= k) ts

-- maksimumi po X i Y
maksimumi :: [Tacka] -> (Float, Float)
maksimumi ts = (maximum $ map fst ts, maximum $ map snd ts)