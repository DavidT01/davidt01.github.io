#Primenom OK metode odrediti kojom brzinom treba ispaliti telo vertikalno uvis da bi stiglo do Meseca,
#ako na njega deluju gravitacione sile Zemlje i Meseca obrnuto proporcionalne rastojanju

import numpy as np

H = 3.84e8
gama = 6.67e-11
Mz = 5.97e24
Mm = 7.348e22
R = 6.378e6
dt = 1e-1
V = 0
korak = 10
h = 0

while h < H:
    h = R
    V += korak
    v = V
    while v >= 0 and h < H:
        v += (-gama * Mz / h**2 + gama * Mm / (H - h)**2) * dt
        h += v * dt
print(V, 'm/s')