#Primenom OK metode odrediti putanju kosmičke letelice, koja je sa Zemlje lansirana
#brzinama iz skupa {0, 1, 2, ..., 10} km/s u pravcu Zemljine heliocentrične orbite.
#Pretpostaviti da se Zemlja kreće po kružnoj putanji oko Sunca, uzeti u obzir samo
#gravitaciju Sunca i vršiti integraciju tokom jedne julijanske godine. Koristiti 
#konstantan vremenski korak kao i korak koji je obrnuto srazmeran ubrzanju. Prikazati
#zavisnost vremena integracije u odnosu na početnu brzinu i naći odnos tih vremena

import numpy as np
import matplotlib.pyplot as plt
import time

Ms = 1.989e30
Rz = 6.378e6
gama = 6.67e-11
AJ = 1.496e11
T = 365.25 * 24 * 60 * 60 #julijanska godina
vorb = 2 * np.pi * AJ / T
V0 = np.arange(0, 11e3, 1e3)
dt0 = 100
odnos = []

for v0 in (V0):
    #dt = const
    X = [AJ]
    Y = [0]
    vx = 0
    vy = vorb + v0
    t = 0
    dt = dt0
    pocetak = time.time()
    while t < T:
        ax = -gama * Ms / (X[-1]**2 + Y[-1]**2)**(3/2) * X[-1]
        ay = -gama * Ms / (X[-1]**2 + Y[-1]**2)**(3/2) * Y[-1]
        vx += ax * dt
        vy += ay * dt
        X.append(X[-1] + vx * dt)
        Y.append(Y[-1] + vy * dt)
        t += dt
    vreme1 = time.time() - pocetak
    #dt != const
    X2 = [AJ]
    Y2 = [0]
    vx = 0
    vy = vorb + v0
    t = 0
    pocetak = time.time()
    while t < T:
        dt = dt0 * (X2[-1]**2 + Y2[-1]**2)**(1/2) / AJ
        ax = -gama * Ms / (X2[-1]**2 + Y2[-1]**2)**(3/2) * X2[-1]
        ay = -gama * Ms / (X2[-1]**2 + Y2[-1]**2)**(3/2) * Y2[-1]
        vx += ax * dt
        vy += ay * dt
        X2.append(X2[-1] + vx * dt)
        Y2.append(Y2[-1] + vy * dt)
        t += dt
    vreme2 = time.time() - pocetak
    odnos.append(vreme1 / vreme2)
    
X = np.array(X)
Y = np.array(Y)
X2 = np.array(X2)
Y2 = np.array(Y2)

plt.figure(1)
plt.plot(X / AJ, Y / AJ, 'r', label = 'Konstantan vremenski korak')
plt.plot(X2 / AJ, Y2 / AJ, 'g', label = 'Promenljiv vremenski korak')
plt.plot(0, 0, 'oy', label = 'Sunce')
plt.legend()
plt.grid()

plt.figure(2)
plt.plot(odnos, V0, label = 'Zavisnost odnosa vremena izvršavanja od početne brzine')
plt.legend()
plt.grid()
plt.show()