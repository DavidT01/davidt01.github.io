#Odrediti rad sile otpora vazduha

import numpy as np

g = 9.81
m = 250
ro0 = 1.23
H = 10000
CS = 0.5
BC = m / CS #balistički koeficijent
dt = 1e-1
hh = [] #čuvamo visine
h = H
v = 0
w = 0

while h >= 0:
    ro = ro0 * np.exp(- h / H)
    a0 = -0.5 * ro * v**2 / BC
    v += (g + a0) * dt
    h -= v * dt
    hh.append(h)
    if(len(hh) > 1):
        w -= m * a0 * (hh[-2] - hh[-1]) #minus jer se visina smanjuje

print('Rad =', w / 1000, 'kJ')