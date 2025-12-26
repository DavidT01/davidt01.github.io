kvadrat(Vars) :- Vars = [X],
    X :: 1..100,
    Y * Y #= X,
    labeling(Vars).