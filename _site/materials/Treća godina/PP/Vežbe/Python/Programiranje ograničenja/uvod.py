import constraint

# Klasa koju koristimo za opisivanje problema
problem = constraint.Problem()

# Pojedinačno dodajemo promenljive
problem.addVariable('a', [1, 2, 5])
problem.addVariable('b', ['a', 'b', 'c'])
problem.addVariable('cd', [1.0, 2.3, 3.3]) # jedna promenljiva cd

# Možemo dodati promenljive zajedno ako imaju isti domen
problem.addVariables(['x', 'y'], range(10))
problem.addVariables(['pqr'], range(10)) # 3 promenljive - p, q i r

# Funkcija koja predstavlja ograničenje vraća True/False
def ogranicenje(x, y, z):
    return x + y + z == 20

# Ograničenje nad promenljivama x, y i z, ograničenje je funkcija
problem.addConstraint(ogranicenje, ['x', 'y', 'z'])
# Možemo zadati i predefinisana ograničenja
problem.addConstraint(constraint.AllDifferentConstraint()) # ako ne navedemo promenljive, odnosi se na sve

# Vraća sva rešenja
resenja = problem.getSolutions()
for r in resenja:
    print(r) # ispisuje rešenje za svaku promenljivu
    print(r['a']) # ispisuje rešenje promenljive 'a'