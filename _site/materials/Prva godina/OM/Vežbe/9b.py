#Prikazati odnos vremena izvršavanja kodova (oba slučaja vremenskog koraka) od početne brzine v0

import numpy as np
import matplotlib.pyplot as plt
import time

GM = 3.983324e14
R = 6.371e6
V = np.arange(2000, 10000, 500)
dt = 1e-2
odnos = []

for i in range(len(V)):
    #dt = const
    pocetak1 = time.time()
    v = V[i]
    r = R
    while v >= 0:
        v -= GM / r**2 * dt
        r += v * dt
    h1 = r - R
    vreme1 = time.time() - pocetak1
    #dt != const
    pocetak2 = time.time()
    v = V[i]
    r = R
    c = GM * dt / R**2
    while v >= 0:
        DT = c * r**2 / GM
        v -= GM / r**2 * DT
        r += v * DT
    h2 = r - R
    vreme2 = time.time() - pocetak2
    odnos.append(vreme2 / vreme1)
    
plt.figure(1)
plt.plot(V, odnos)
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Odnos vremena izvršavanja [s]')
plt.grid()
plt.show()