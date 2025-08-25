#Prikazati zavisnost dometa od ugla i brzine za, uglove iz skupa {0, 1, 2, ..., 90} i brzine iz skupa {50, 51, 52, ..., 100}

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

v = np.arange(50, 101, 1)
alfa = np.arange(0, 91, 1)
alfa = np.deg2rad(alfa)
domet = np.zeros([len(v), len(alfa)])
ax = 0
ay = -9.81
dt = 1e-3

for i in range(0, len(v)):
    for j in range(0, len(alfa)):
        x = 0
        y = 0
        vx = v[i] * np.cos(alfa[j])
        vy = v[i] * np.sin(alfa[j])
        while y >= 0:
            x += vx * dt
            y += vy * dt
            vx += ax * dt
            vy += ay * dt
        domet[i][j] = x
        
#2D plotovanje        
plt.figure(1)
plt.contour(np.rad2deg(alfa), v, domet, 20, cmap = cm.jet)
plt.xlabel('Ugao [deg]')
plt.ylabel('Brzina [m/s]')
plt.colorbar()
#plt.show()

#3D plotovanje
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, projection = '3d')
alfa, v = np.meshgrid(alfa, v)
ax.plot_surface(v, np.rad2deg(alfa), domet, cmap = cm.jet, linewidth = 0, antialiased = False)
ax.set_xlabel('Brzina [m/s')
ax.set_ylabel('Ugao [deg]')
ax.set_zlabel('Domet [m]')
plt.show()