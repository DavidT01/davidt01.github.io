#Prikazati zavisnost brzine i vremena od visine h za proizvoljno izabrani fiksirani vremenski korak

import numpy as np
import matplotlib.pyplot as plt

g =- 9.81
dt = 1e-2
H = np.linspace(10, 10000, 100)
V = np.zeros_like(H)
T = np.zeros_like(H)

for i, h in enumerate(H):
    v = 0
    t = 0
    while h > 0:
        h += v * dt
        v += g * dt
        t += dt  
    V[i] = v
    T[i] = t

plt.figure(1)
plt.plot(H, V)
plt.xlabel('Početna visina [m]')
plt.ylabel('Brzina udara [m/s]')
plt.title('Zavisnost brzine od početne visine')

plt.figure(2)
plt.plot(H, T)
plt.xlabel('Početna visina [m]')
plt.ylabel('Vreme padanja [m/s]')
plt.title('Zavisnost vremena padanja od početne visine')
plt.show()