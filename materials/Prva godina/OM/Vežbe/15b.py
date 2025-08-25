#Primenom OK metode odrediti putanju kosmičke letelice koja je sa Zemlje lansirana brzinom 10 km/s u pravcu
#normalnom na Zemljinu heliocentričnu brzinu. Pretpostaviti da se Zemlja kreće po kružnoj putanji oko Sunca.
#Uzeti u obzir i silu gravitacije Sunca i silu gravitacije Zemlje tokom jedne julijanske godine (362.25 dana)

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

Ms = 1.989e30
Mz = 5.972e24
Rz = 6.378e6
AJ = 1.5e11
gama = 6.67e-11
julgod = 362.25 * 24 * 60 * 60 #jedna julijanska godina u sekundama
omega = 2 * np.pi / julgod #ugaono ubrazanje
v0 = 10000
vorb = 2 * np.pi * AJ / (365.25 * 24 * 60 * 60)
dt = 1000
t = 0

#Početni uslovi za letelicu (heliocentrični sistem)
X = [AJ + Rz]
Y = [0]
Z = [0]
vx = 0
vy = vorb
vz = v0
#Početni uslovi za Zemlju (heliocentrični sistem)
Xz = [AJ]
Yz = [0]
Zz = [0]
#Početni uslovi za letelicu (geocentrični sistem)
Xgc = [Rz]
Ygc = [0]
Zgc = [0]

while t <= julgod: #dok ne prođe jedna julijanska godina
    ax = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * X[-1] -gama * Mz / (Xgc[-1]**2 + Ygc[-1]**2 + Zgc[-1]**2)**(3/2) * Xgc[-1]
    ay = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * Y[-1] -gama * Mz / (Xgc[-1]**2 + Ygc[-1]**2 + Zgc[-1]**2)**(3/2) * Ygc[-1]
    az = -gama * Ms / (X[-1]**2 + Y[-1]**2 + Z[-1]**2)**(3/2) * Z[-1] -gama * Mz / (Xgc[-1]**2 + Ygc[-1]**2 + Zgc[-1]**2)**(3/2) * Zgc[-1]
    vx += ax * dt
    vy += ay * dt
    vz += az * dt
    X.append(X[-1] + vx * dt)
    Y.append(Y[-1] + vy * dt)
    Z.append(Z[-1] + vz * dt)
    lz = omega * t #longituda (ugao)
    Xz.append(AJ * np.cos(lz))
    Yz.append(AJ * np.sin(lz))
    Zz.append(0)
    Xgc.append(X[-1] - Xz[-1])
    Ygc.append(Y[-1] - Yz[-1])
    Zgc.append(Z[-1] - Zz[-1])
    t += dt

#Prebacimo liste u nizove zbog 3D plotovanja
X1 = np.array(X)
Y1 = np.array(Y)
Z1 = np.array(Z)
X2 = np.array(Xz)
Y2 = np.array(Yz)
Z2 = np.array(Zz)

#3D plot
fig = plt.figure(1)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
ax.set_xlim3d(-1.5, 1.5)
ax.set_ylim3d(-1.5, 1.5)
ax.set_zlim3d(-1.5, 1.5)
plt.plot(X1 / AJ, Y1 / AJ, Z1 / AJ, 'r', label='putanja letelice') #putanja letelice
plt.plot(X2 / AJ, Y2 / AJ, Z2 / AJ, 'b', label='putanja Zemlje') #putanja Zemlje
plt.plot(0, 0, 0, 'oy', label='Sunce') #Sunce
plt.legend()
plt.show()