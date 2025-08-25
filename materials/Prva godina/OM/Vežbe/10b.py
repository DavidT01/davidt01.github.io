#Kako se menja razlika dometa u slučajevima bez i sa otporom za različite gustine sredina?
#Uzeti da su vrednosti za gustinu iz intervala (0.2, 0.3, ..., 2.5)

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
CS = 0.001
m = 1
v0 = 100
alfa = np.deg2rad(45)
dt = 1e-2
RO = np.arange(0.2, 2.5, 0.1)
razlike = np.zeros_like(RO)

for i, ro in enumerate(RO):
    #Bez otpora
    x = 0
    y = 0
    vx = v0 * np.cos(alfa)
    vy = v0 * np.sin(alfa)
    while y >= 0:
        vy -= g*dt
        x += vx * dt
        y += vy *dt
    #Sa otporom
    xo = 0
    yo = 0
    vxo = v0 * np.cos(alfa)
    vyo = v0 * np.sin(alfa)
    while yo >= 0:
        vo = np.sqrt(vxo**2 + vyo**2)
        axo = -(CS * ro * vo * vxo) / (2 * m)
        ayo = -g - (CS * ro * vo * vyo) / (2 * m)
        vxo += axo * dt
        vyo += ayo * dt
        xo += vxo * dt
        yo += vyo * dt
    razlike[i] = np.abs(x - xo) #postignuti dometi će biti poslednje x, odnosno xo
    
#Plotovanje
plt.figure(1)
plt.title('Zavisnost razlike u dometima od gustine')
plt.plot(RO, razlike, 'r')
plt.xlabel('Gustina [kg/m^3]')
plt.ylabel('Razlika u dometu sa i bez otpora [m]')
plt.grid()
plt.show()