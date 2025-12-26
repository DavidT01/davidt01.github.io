#Primenom OK metode odrediti putanju kosmičke letelice koja je sa Zemlje lansirana brzinom 10 km/s u pravcu
#normalnom na Zemljinu heliocentričnu brzinu. Pretpostaviti da se Zemlja kreće po kružnoj putanji oko Sunca.
#Uzeti u obzir samo silu gravitacije Sunca

#Isto kao 14, ali su drugačiji početni uslovi i beležimo z osu

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

Ms = 1.989e30
Rz = 6.378e6
AJ = 1.5e11
gama = 6.67e-11
dt = 1000
v0 = 10000
vorb = 2 * np.pi * AJ / (365.25 * 24 * 60 * 60)

#Početni uslovi za letelicu (heliocentrični sistem)
X = [AJ + Rz]
Y = [0]
Z = [0]
vx = 0
vy = vorb
vz = v0
fi = [np.arctan2(Y, X)]

while len(fi) == 1 or fi[-1] > fi[-2]: #ugao se stalno povećava
    ax = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * X[-1]
    ay = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * Y[-1]
    az = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * Z[-1]
    vx += ax * dt
    vy += ay * dt
    vz += az * dt
    X.append(X[-1] + vx * dt)
    Y.append(Y[-1] + vy * dt)
    Z.append(Z[-1] + vz * dt)
    fi.append(np.mod(np.arctan2(Y[-1], X[-1]), 2 * np.pi)) #prebacimo negativne vrednosti u pozitivne pomoću ostatka

#Prebacimo liste u nizove zbog 3D plotovanja
X1 = np.array(X)
Y1 = np.array(Y)
Z1 = np.array(Z)

#3D plot
fig = plt.figure(1)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
ax.set_xlim3d(-1.5, 1.5)
ax.set_ylim3d(-1.5, 1.5)
ax.set_zlim3d(-1.5, 1.5)
plt.plot(X1 / AJ, Y1 / AJ, Z1 / AJ, 'r', label='putanja letelice') #putanja
plt.plot(0, 0, 0, 'oy', label='Sunce') #Sunce
plt.plot(1, 0, 0, 'og', label='Zemlja') #Zemlja u nekom položaju
plt.legend()
plt.show()