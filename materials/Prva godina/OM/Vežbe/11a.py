#Primenom OK metode odrediti kojom brzinom treba ispaliti telo vertikalno uvis da bi stiglo do Meseca,
#ako na njega deluje samo homogeno polje Zemljine tеže

import numpy as np

H = 3.84e8 #udaljenost Meseca
g = -9.81
dt = 1e-1
V = 0
korak = 100
h = 0

while h < H:
    h = 0
    V += korak
    v = V
    while v >= 0:
        v += g * dt
        h += v * dt
print(V, 'm/s')