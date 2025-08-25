/* 1) Generisanje promenljivih i njihovih domena
*
*       X in D ili X :: D 
*       Vars in D ili Vars :: D
*       D = pocetak..korak..kraj 
*
*    2) Ogranicenja
*
*       1) opsta
*            alldifferent(vars) ili alldistrinct(Vars) % sve razlicite vrednosti
*            atmost(N, L, V) % najvise N elemenata L je jednako V
*            atleast(N, L, V) % bar N elemenata L je jednako V
*            exactly(N, L, V) % tacno N elemenata L je jednako V
*
*       2) aritmeticka
*           I1 R I2, R -> {#=, #\=, #>=, #>, ...}
*           min(L)
*           max(L)
*           sum(L)
*
*    3) Instanciranje
*       
*       labeling(Vars) ili labeling(Options, Vars)
*       Options: minimize(E), maximize(E)
*           
*
*
*/

% Naci X, Y, Z tako da:
% X <- 1, 2, 3,
% Y <- 2, 4, 6, 8, 10
% Z <- 5, 6, 7, 8
% Z >= Y

primer(Vars) :- Vars = [X, Y, Z], % definisanje promenljivih
    X :: 1..3,
    Y :: 2..2..10,
    Z :: 5..8, % definisanje domena
    Z #>= Y, % definisanje ogranicenja
    labeling(Vars). % instanciranje