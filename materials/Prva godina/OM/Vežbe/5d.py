#Odrediti i prikazati na koji način vreme izvršavanja koda zavisi od početne brzine

import numpy as np
import matplotlib.pyplot as plt
import time

gamaM = 3.983324e14
R = 6.371e6
V = np.arange(100, 10000, 100)
T = []
dt = 1e-2

for i, v in enumerate(V):
    r = R
    pocetak = time.time()
    while v > 0:
        v -= gamaM / r**2 * dt
        r += v * dt
    T.append(time.time() - pocetak)
    
plt.figure(1)
plt.plot(V, T, 'r')
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Vreme izvršavanja [s]')
plt.show()