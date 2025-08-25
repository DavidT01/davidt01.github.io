#Prikazati razlike visina (u odnosu na analitičko rešenje) u zavisnosti od početne brzine

import numpy as np
import matplotlib.pyplot as plt

GM = 3.983324e14
R = 6.371e6
V = np.arange(2000, 10000, 500)
dt = 1e-2
razlike1 = [] #dt = const
razlike2 = [] #dt != const

#Analitičko rešenje
Ha = V**2 * R**2 / (2 * GM - R * V**2)

for i in range(len(V)):
    #dt = const
    v = V[i]
    r = R
    while v >= 0:
        v -= GM / r**2 * dt
        r += v * dt
    h1 = r - R
    razlike1.append(abs(h1 - Ha[i] * 100 / Ha[i]))
    #dt != const
    v = V[i]
    r = R
    c = GM * dt / R**2
    while v >= 0:
        DT = c * r**2 / GM
        v -= GM / r**2 * DT
        r += v * DT
    h2 = r - R
    razlike2.append(abs(h2 - Ha[i] * 100 / Ha[i]))
    
plt.figure(1)
plt.plot(V, razlike1, 'r')
plt.plot(V, razlike2)
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Razlike visina [%]')
plt.grid()
plt.show()