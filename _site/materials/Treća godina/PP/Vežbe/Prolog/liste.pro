% prazna lista: []
% konstruktor: .(Glava, Rep) ili [Glava, Rep]

% Unifikacija
% [X, Y, Z] = [a, b, c] => X = a, Y = b, Z = c
% [a] = [X | Y] => X = a, Y = []
% [a, b, c] = [X, Y | Z] => X = a, Y = b, Z = [c]

% da li se X nalazi u listi L

sadrzi(X, [X | _]).
sadrzi(X, [_ | R]) :- sadrzi(X, R).

% duzina liste

duzina([], 0).
duzina([_ | R], D) :- duzina(R, D1), D is D1 + 1.

% suma liste

suma([], 0).
suma([G | R], S) :- number(G), suma(R, S1), S is S1 + G.

% aritmeticka sredina

arsr([], 0) :- !. % cut da se ne bi delilo nulom ako je prazna lista
arsr(L, A) :- suma(L, S), duzina(L, D), A is S / D.

% ucitavanje N elemenata u listu

ucitaj(N, _) :- N < 0, !, fail.
ucitaj(0, []) :- !.
ucitaj(N, [G | R]) :- write('Unesi broj'), nl, read(G), N1 is N - 1, ucitaj(N1, R). % nl je novi red