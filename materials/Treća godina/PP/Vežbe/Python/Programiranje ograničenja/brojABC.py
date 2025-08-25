# Napisati program koji pronalazi trocifren broj ABC tako da je količnik ABC / (A + B + C)
# minimalan i A, B i C su različiti brojevi.

import constraint

problem = constraint.Problem()

problem.addVariable('A', range(1, 10))
problem.addVariables(['B', 'C'], range(10))

problem.addConstraint(constraint.AllDifferentConstraint())

# Delimo trocifren broj sa nečim pa gornja granica može biti 1000
min_kol = 1000
broj = 0
for resenje in problem.getSolutions():
    a, b, c = resenje['A'], resenje['B'], resenje['C']
    kol = (100*a + 10*b + c) / (a + b + c)
    if kol < min_kol:
        min_kol = kol
        broj = 100*a + 10*b + c
print(broj, min_kol)