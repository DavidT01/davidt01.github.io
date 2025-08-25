% Zivotinje

zivotinja(slon). % cinjenica da je slov zivotinja
zivotinja(vuk).
zivotinja(zec).
zivotinja(zebra).

veci(slon, vuk). % cinjenica da je slon veci od vuka (binarni operator)
veci(vuk, zec).

jeVeci(X, Y) :- veci(X, Y). % pravilo
jeVeci(X, Y) :- veci(X, Z), jeVeci(Z, Y).

% Godine

prestupna(X) :- X mod 400 =:= 0.
prestupna(X) :- X mod 4 =:= 0, X mod 100 =\= 0.

% Dani u mesecu

brdana(januar, _, 31). % koja god godina da je u pitanju, januar ima 31 dan
brdana(februar, X, 29) :- prestupna(X), !. % cut operator jer necemo da gledamo drugu granu ako nadjemo resenje u prvoj
brdana(februar, X, 28) :- not(prestupna(X)). % ovde moze i da se obrise uslov:
% brdana(februar, X, 29).
brdana(mart, _, 31).
brdana(april, _, 30).
brdana(maj, _, 31).
brdana(jun, _, 30).
brdana(jul, _, 31).
brdana(avgust, _, 31).
brdana(septembar, _, 30).
brdana(oktobar, _, 31).
brdana(novembar, _, 30).
brdana(decembar, _, 31).

% Porodicno stablo

musko(mihajlo).
musko(stevan).
musko(petar).
musko(mladen).
musko(rajko).

zensko(milena).
zensko(milica).
zensko(jelena).
zensko(senka).
zensko(mina).
zensko(maja).
zensko(ana).

roditelj(ana, mihajlo).
roditelj(mihajlo, milica).
roditelj(mihajlo, senka).
roditelj(milena, rajko).
roditelj(maja, petar).
roditelj(maja, mina).
roditelj(stevan, mladen).
roditelj(stevan, jelena).
roditelj(milica, mladen).
roditelj(milica, jelena).

% X je majka/otac od Y
majka(X, Y) :- roditelj(X, Y), zensko(X).
otac(X, Y) :- roditelj(X, Y), musko(X).

% X je brat od Y
brat(X, Y) :- musko(X), roditelj(Z, X), roditelj(Z, Y).

% X j predak od Y
predak(X, Y) :- roditelj(X, Y).
predak(X, Y) :- roditelj(X, Z), predak(Z, Y).

% S je suma prvih N prirodnih brojeva
suma(1, 1) :- !.
suma(N, S) :- N1 is N - 1, suma(N1, S1), S is N + S1.