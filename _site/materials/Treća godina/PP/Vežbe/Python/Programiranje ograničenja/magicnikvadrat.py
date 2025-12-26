# Napisati program koji ređa brojeve u magičan kvadrat. Magičan kvadrat
# je kvadrat dimenzija 3x3 takav da je suma svih brojeva u svakom redu, svakoj koloni i svakoj
# dijagonali jednak 15 i svi brojevi različiti. Na primer:
# 4 9 2
# 3 5 7
# 8 1 6

import constraint

problem = constraint.Problem()

# a b c
# d e f
# g h i

problem.addVariables('abcdefghi', range(1, 10))

def ogr(a, b, c, d, e, f, g, h, i):
    return a + b + c == 15 and d + e + f == 15 and g + h + i == 15 and \
        a + d + g == 15 and b + e + h == 15 and c + f + i == 15 and \
            a + e + i == 15 and c + e + g == 15
            
problem.addConstraint(ogr, ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'])
problem.addConstraint(constraint.AllDifferentConstraint())

resenja = problem.getSolutions()
print(len(resenja), '\n')
for r in resenja:
    print(f"{r['a']} {r['b']} {r['c']}\n{r['d']} {r['e']} {r['f']}\n{r['g']} {r['h']} {r['i']}\n----------\n")