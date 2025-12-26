#Padobranac slobodno pada sa visine od 2 km. Pored sile Zemljine teže na njega deluje i sila otpora
#vazduha data kao F = - m * k * v. Pomoću OK metode odrediti zavisnost brzine od vremena i prikazati

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
k = 0.17658 #1/2, koeficijent
H = 2000
dt = 1e-2
t = 0
v = 0
V = []
T = []

while H >= 0:
    v += (g - k * v) * dt
    H -= v * dt
    t += dt
    V.append(v)
    T.append(t)

plt.figure(1)
plt.plot(T, V, 'r', label = 'Trenutna brzina')
plt.plot(T, np.ones_like(T) * g / k, '--', label = 'Asimptotska brzina')
plt.title('Zavisnost brzine od vremena')
plt.xlabel('Vreme [s]')
plt.ylabel('Brzina [m/s]')
plt.legend()
plt.grid()
plt.show()