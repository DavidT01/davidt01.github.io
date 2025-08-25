#Odrediti i prikazati na koji način ova visina zavisi od početne brzine (uporediti i sa analitičkim rešenjem h = v0^2 / 2g)

import numpy as np
import matplotlib.pyplot as plt

gamaM = 3.983324e14
R = 6.371e6
g = 9.81
V = np.arange(100, 10000, 100)
H = np.zeros_like(V)
dt = 1e-2

#Analitičko rešenje:
visina = V**2 / (2 * g)

for i, v in enumerate(V):
    r = R
    while v > 0:
        v -= gamaM / r**2 * dt
        r+= v * dt
    H[i] = (r - R) / 1000
    
plt.figure(1)
plt.plot(V, H, 'r') #zavisnost visine od početne brzine
plt.plot(V, visina / 1000, 'b') #poređenje sa analitičkim rešenjem
plt.xlabel("Brzina [m/s]")
plt.ylabel("Visina [km]")
plt.show()