# map primenjuje funkciju na listu prosleđenih objekata, npr:
def g(x):
    return 2*x + 1
map(g, [1, 2, 3, 4, 5]) # [g(1), g(2), g(3), g(4), g(5)] -> [3, 5, 7, 9, 11]

# filter izdvaja elemente za koje funkcija vraća True, npr:
def f(x):
   if x < 4:
       return True
filter(f, [1, 2, 3, 4, 5]) # [1, 2, 3]

# zip uparuje elemente nekoliko listi, npr:
zip([1, 2], ['a', 'b']) # [(1, 'a'), (2, 'b')]

# reduce primenjuje funkciju redom na sve elemente liste, tj. "svodi" listu na jednu vrednost
from functools import reduce
brojevi = range(11)
suma = reduce(lambda x, y: x + y, brojevi) # 55

# Sortiranje
l = [2, 5, 1, 4, 3, 4, 7, 0]
print(sorted(l)) # rastuće
print(sorted(l, reverse = True)) # opadajuće

l1 = [{'indeks': 'mi20049'}, {'indeks': 'mi21102'}, {'indeks': 'mi20034'}]
print(sorted(l1, key = lambda x: x['indeks'])) # naznačili smo da sortiramo po indeksu

# Pisanje "komparatora"
from functools import cmp_to_key
print(sorted(l, key = cmp_to_key(lambda x, y: x > y)))