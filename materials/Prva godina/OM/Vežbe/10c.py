#Prikazati na koji način domet i maksimalna visina zavise od mase u oba slučaja

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
CS = 0.001
ro = 1.23
v0 = 100
alfa = np.deg2rad(45)
M = np.arange(100, 10000, 100)
Do = np.zeros_like(M)
Ho = np.zeros_like(M)
dt = 1e-2

#Bez otpora - ne zavisi od mase (D i H će biti const)
Y = []
x = 0
y = 0
vx = v0 * np.cos(alfa)
vy = v0 * np.sin(alfa)
while y >= 0:
    vy -= g*dt
    x += vx * dt
    y += vy *dt
    Y.append(y)
D = np.ones_like(M) * x
h = np.max(Y)
H = np.ones_like(M) * h

#Sa otporom
Yo = [[] for column in range(len(M))]
xo = 0
yo = 0
vxo = v0 * np.cos(alfa)
vyo = v0 * np.sin(alfa)
for i, m in enumerate(M):
    while yo >= 0:
        vo = np.sqrt(vxo**2 + vyo**2)
        axo = - (CS * ro * vo * vxo) / (2 * m)
        ayo = -g - (CS * ro * vo * vyo) / (2 * m)
        vxo += axo * dt
        vyo += ayo * dt
        xo += vxo * dt
        yo += vyo * dt
        Yo[i].append(yo)
    Do[i] = xo

for i in range(len(Yo)):
    ho = np.max(Yo[i])
    Ho[i] = ho
    
plt.figure(1)
plt.plot(M, D, '--b')
plt.plot(M, Do, '--r')
plt.plot(M, H, '.b')
plt.plot(M, Ho, '.r')
plt.grid()
plt.show()