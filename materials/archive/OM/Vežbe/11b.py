#Primenom OK metode odrediti kojom brzinom treba ispaliti telo vertikalno uvis da bi stiglo do Meseca,
#ako na njega deluje gravitaciona sila Zemlje obrnuto proporcionalna rastojanju

import numpy as np

H = 3.84e8
gama = 6.67e-11
M = 5.97e24
R = 6.378e6
dt = 1e-1
V = 0
korak = 10
h = 0

while h < H:
    h = R
    V += korak
    v = V
    while v >= 0:
        v -= gama*M / h**2 * dt
        h += v * dt
print(V, 'm/s')