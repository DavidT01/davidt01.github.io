% Da li je X u listi L
clan(X, [X | _]).
clan(X, [_ | R]) :- clan(X, R).

% X je desno od Y u listi L
desno(X, Y, [Y, X | _]).
desno(X, Y, [_ | R]) :- desno(X, Y, R).

% X je pored Y u listi L
pored(X, Y, [X, Y | _]).
pored(X, Y, [Y, X | _]).
pored(X, Y, [_ | R]) :- pored(X, Y, R).

% k(boja, nacionalnost, jelo, pice, ljubimac)
kuce(L) :-  L = [k(_, norvezanin, _, _, _),
                k(plava, _, _, _, _),
                k(_, _, _, mleko, _),
                k(_, _, _, _, _),
                k(_, _, _, _, _)],
            clan(k(crvena, englez, _, _, _), L),
            clan(k(_, spanac, _, _, pas), L),
            clan(k(zelena, _, _, kafa, _), L),
            clan(k(_, ukrajinac, _, caj, _), L),
            desno(k(zelena, _, _, kafa, _), k(bela, _, _, _, _), L),
            clan(k(_, _, spagete, _, puz), L),
            clan(k(zuta, _, pizza, _, _), L),
            pored(k(_, _, piletina, _, _), k(_, _, _, _, lisica), L),
            pored(k(_, _, pizza, _, _), k(_, _, _, _, konj), L),
            clan(k(_, _, brokoli, sok, _), L),
            clan(k(_, japanac, sushi, _, _), L),
            clan(k(_, _, _, _, zebra), L),
            clan(k(_, _, _, voda, _), L).

% Cija je zebra, a ko pije vodu?
zagonetka(X, Y) :- kuce(L), clan(k(_, X, _, _, zebra), L), clan(k(_, Y, _, voda, _), L).