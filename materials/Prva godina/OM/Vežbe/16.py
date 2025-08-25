#Primenom OK metode odrediti geocentričnu i heliocentričnu putanju kosmičke letelice koja je sa
#udaljenosti od 50 Zemljinih poluprečnika od Zemlje preusmerila kretanje brzinom v =  v0 * ey + 1/2 * v0 * ez.
#Uzeti u obzir i gravitaciju Zemlje i gravitaciju Sunca i posmatrati kretanje tokom jedne julijanske godine.
#Za početnu brzinu uzeti 1 km/s

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
v0 = 1000
vorb = 2 * np.pi * AJ / (365.25 * 24 * 60 * 60)
dt = 1000
t = 0

#Početni uslovi za letelicu (heliocentrični sistem)
X = [AJ + 50 * Rz]
Y = [0]
Z = [0]
vx = 0
vy = vorb + v0
vz = v0 / 2
#Početni uslovi za Zemlju (heliocentrični sistem)
Xz = [AJ]
Yz = [0]
Zz = [0]
#Početni uslovi za letelicu (geocentrični sistem)
Xgc = [50 * Rz]
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
X3 = np.array(Xgc)
Y3 = np.array(Ygc)
Z3 = np.array(Zgc)

#Heliocentrična putanja letelice
fig = plt.figure(1)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
plt.title('Heliocentrična putanja letelice')
plt.plot(X1 / AJ, Y1 / AJ, Z1 / AJ, 'r', label='putanja letelice') #putanja letelice
plt.plot(X2 / AJ, Y2 / AJ, Z2 / AJ, 'b', label='putanja Zemlje') #putanja Zemlje
plt.plot(0, 0, 0, 'oy', label='Sunce') #Sunce
plt.legend()

#Geocentrična putanja letelice
fig = plt.figure(2)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
plt.title('Geocentrična putanja letelice')
plt.plot(X3 / Rz, Y3 / Rz, Z3 / Rz, 'r', label='putanja letelice') #putanja letelice
plt.plot(0, 0, 0, 'og', label='Zemlja') #Zemlja
plt.legend()
plt.show()