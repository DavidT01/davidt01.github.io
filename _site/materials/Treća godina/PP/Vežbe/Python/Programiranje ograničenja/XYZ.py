# Napisati program koji pronalazi sve vrednosti promenljivih X, Y i Z za koje
# važi da je X >= Z i X ∗ 2 + Y ∗ X + Z <= 34 pri čemu promenljive pripadaju narednim domenima
# X ∈ {1, 2, ..., 90}, Y ∈ {2, 4, 6, ..., 60} i Z ∈ {1, 4, 9, 16, ..., 100}

import constraint

problem = constraint.Problem()

problem.addVariable('X', range(1, 91))
problem.addVariable('Y', range(2, 61, 2))
problem.addVariable('Z', [i**2 for i in range(1, 11)])

def ogr(X, Y, Z):
    return 2*X + Y*X + Z <= 34

def ogr2(X, Z):
    return X >= Z

problem.addConstraint(ogr, ['X', 'Y', 'Z'])
problem.addConstraint(ogr2, ['X', 'Z'])
# Ili oba uslova u jednu funkciju, tj. ograničenje

print(len(problem.getSolutions()))