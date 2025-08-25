#Za maksimalni domet kosog hica odrediti putanje korišćenjem Ojlerove i Ojler-Kromerove metode. 
#Koliko maksimalni domet odstupa od analitičkog rešenja i kako ovo odstupanje zavisi od vremenskog koraka?

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
v = 100
alfa = np.deg2rad(45)
DT = np.arange(1e-2, 1, 1e-2)
D_o = np.zeros(len(DT)) #Ojlerova
D_ok = np.zeros_like(DT) #Ojler-Kromerova

#Analitičko rešenje:
domet = v**2 * np.sin(2 * alfa) / g

ax = 0
ay = -9.81

for i, dt in enumerate(DT):
#Ojlerova metoda:
    x = 0
    y = 0
    vx = v * np.cos(alfa)
    vy = v * np.sin(alfa)
    while y >= 0:
        x += vx * dt
        y += vy * dt
        vx += ax * dt
        vy += ay * dt
    D_o[i] = x
    
#Ojler-Kromerova metoda:
    x = 0
    y = 0
    vx = v * np.cos(alfa)
    vy = v * np.sin(alfa)
    while y >= 0:
        vx += ax * dt
        vy += ay * dt
        x += vx * dt
        y += vy * dt
    D_ok[i] = x

#Putanje
plt.figure(1)
plt.plot(DT, D_o, 'r') #crven
plt.plot(DT, D_ok) #plav (default)

#Odstupanje u zavisnosti od vremenskog koraka
plt.figure(2)
plt.plot(DT, np.abs(D_o - domet), 'r')
plt.plot(DT, np.abs(D_ok - domet))
plt.show()