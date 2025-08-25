#Primenom OK metode odrediti putanju kosmičke letelice koja je sa Zemlje lansirana brzinom 10 km/s
#u smeru heliocentrične brzine Zemlje. Pretpostaviti da se Zemlja kreće kružnom putanjom oko Sunca
#i da deluje samo gravitaciono polje Sunca

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D

Ms = 1.989e30
Rz = 6.378e6
AJ = 1.5e11 #m, astronomska jedinica
gama = 6.67e-11
dt = 1000 #gledamo kretanja tokom cele godine pa uzimamo veći interval
v0 = 10000
vorb = 2 * np.pi * AJ / (365.25 * 24 * 60 * 60) #brzina orbitiranja Zemlje

#Početni uslovi za letelicu (heliocentrični sistem)
X = [AJ + Rz] #rastojanje između Zemlje i Sunca + poluprečnik Zemlje
Y = [0]
Z = [0]
vx = 0
vy = v0 + vorb
vz = 0
fi = [np.arctan2(Y, X)] #vraća ugao iz intervala [-pi, pi] koji je jednak actan(Y / X)

while len(fi) == 1 or fi[-1] > fi[-2]: #ugao se stalno povećava
    ax = -gama * Ms / (X[-1]**2 + Y[-1]**2)**(3/2) * X[-1]
    ay = -gama * Ms / (X[-1]**2 + Y[-1]**2)**(3/2) * Y[-1]
    vx += ax * dt
    vy += ay * dt
    X.append(X[-1] + vx * dt)
    Y.append(Y[-1] + vy * dt)
    fi.append(np.mod(np.arctan2(Y[-1], X[-1]), 2 * np.pi)) #prebacimo negativne vrednosti u pozitivne pomoću ostatka

#Prebacimo liste u nizove zbog 3D plotovanja
X1 = np.array(X)
Y1 = np.array(Y)

#3D plot
fig = plt.figure(1)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
ax.set_xlim3d(-10, 10)
ax.set_ylim3d(-10, 10)
ax.set_zlim3d(-10, 10)
plt.plot(X1 / AJ, Y1 / AJ, np.zeros_like(X1), 'r', label='putanja letelice') #putanja letelice
plt.plot(0, 0, 0, 'oy', label='Sunca') #Sunce
plt.plot(1, 0, 0, 'og', label='Zemlja') #Zemlja u nekom položaju
plt.legend()
plt.show()