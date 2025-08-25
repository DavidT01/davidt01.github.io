#Prikazati na koji način ova brzina i vreme zavise od vremenskog koraka

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
DT = np.arange(1e-4, 1e-2, 1e-4)
V = np.zeros_like(DT)
T = np.zeros_like(DT)

for i, dt in enumerate(DT):
    h = 1000
    v = 0
    t = 0
    while h > 0:
        h += v * dt
        v += g * dt
        t += dt
    V[i] = v
    T[i] = t

plt.figure(1)
plt.plot(DT, V)
plt.xlabel('Vremenski korak [s]')
plt.ylabel('Brzina udara [m/s]')
plt.title('Zavisnost brzine od vremenskog koraka')

plt.figure(2)
plt.plot(DT, T)
plt.xlabel('Vremenski korak [s]')
plt.ylabel('Vreme padanja [s]')
plt.title('Zavisnost vremena padanja od vremenskog koraka')
plt.show()