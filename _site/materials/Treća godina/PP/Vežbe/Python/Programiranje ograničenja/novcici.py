# Dati su novčići od 1, 2, 5, 10, 20 dinara. Napisati program koji pronalazi sve
# moguće kombinacije tako da zbir svih novčića bude 50.

import constraint

problem = constraint.Problem()

problem.addVariable('1 din', range(51))
problem.addVariable('2 din', range(26))
problem.addVariable('5 din', range(11))
problem.addVariable('10 din', range(6))
problem.addVariable('20 din', range(3))

def ogr(a, b, c, d, e):
    return a + 2*b + 5*c + 10*d + 20*e == 50

problem.addConstraint(ogr, ['1 din', '2 din', '5 din', '10 din', '20 din'])
#problem.addConstraint(constraint.ExactSumConstraint(50, [1, 2, 5, 10, 20], ['1 din', '2 din', '5 din', '10 din', '20 din']))

for r in problem.getSolutions():
    print(f"1 din: {r['1 din']}, 2 din: {r['2 din']}, 5 din: {r['5 din']}, 10 din: {r['10 din']}, 20 din: {r['20 din']}\n")