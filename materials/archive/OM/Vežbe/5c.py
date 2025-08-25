#Odrediti i prikazati na koji način vreme penjanja zavisi od brzine (uporediti i sa analitičkim rešenjem t = v0 / g)

import numpy as np
import matplotlib.pyplot as plt

gamaM = 3.983324e14
R = 6.371e6
g = 9.81
V = np.arange(100, 10000, 100)
T = np.zeros_like(V)
dt = 1e-1

#Analitičko rešenje:
vreme = V / g

for i, v in enumerate(V):
    r = R
    t = 0
    while v > 0:
        v -= gamaM / r**2 * dt
        r += v * dt
        t += dt
    T[i] = t
        
plt.figure(1)
plt.plot(V, T, 'r')
plt.plot(V, vreme, 'b')
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Vreme penjanja [s]')
plt.show()