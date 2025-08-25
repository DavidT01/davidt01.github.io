#Prikazati na koji način domet zavisi od početne brzine, ugla i mase sa silom otpora

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

g = 9.81
CS = 0.001
ro = 1.23
v0 = np.arange(10, 100, 10)
alfa = np.deg2rad(np.arange(10, 80, 10))
M = np.arange(100, 10000, 100)
D = np.zeros([len(v0), len(alfa), len(M)])
dt = 1e-2

for i in range(len(v0)):
    for j in range(len(alfa)):
        for k in range(len(M)):    
            xo = 0
            yo = 0
            vxo = v0[i] * np.cos(alfa[j])
            vyo = v0[i] * np.sin(alfa[j])
            while yo >= 0:
                vo = np.sqrt(vxo**2 + vyo**2)
                axo = -(CS * ro * vo * vxo) / (2 * M[k])
                ayo = -g -(CS * ro * vo * vyo) / (2 * M[k])
                vxo += axo * dt
                vyo += ayo * dt
                xo += vxo * dt
                yo += vyo * dt
            D[i][j][k] = xo

fig = plt.figure(1)
ax = fig.add_subplot(1, 1, 1, projection = '3d')
ALFA, V = np.meshgrid(alfa, v0)
for i in range(len(M)):
    ax.plot_surface(np.rad2deg(ALFA), V, D[:, :, i])
ax.set_xlabel('Ugao [deg]')
ax.set_ylabel('Početna brzina [m/s]')
ax.set_zlabel('Domet [m]')
plt.show()