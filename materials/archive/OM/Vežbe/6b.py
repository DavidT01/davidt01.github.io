#Odrediti i prikazati na koji način domet zavisi od uglova alfa i beta

import numpy as np
import matplotlib.pyplot as plt

from matplotlib import cm

g = -9.81
beta = np.deg2rad(np.arange(-30, 0))
alfa = np.deg2rad(np.arange(0, 50))
v = 300
dt = 1e-1
domet = np.zeros([len(beta), len(alfa)])

for i in range(len(beta)):
    for j in range(len(alfa)):
        x = 0
        y = 0
        vx = v * np.cos(alfa[j])
        vy = v * np.sin(alfa[j])
        while x == 0 or y / x > np.tan(beta[i]):
            vy += g * dt
            x += vx * dt
            y += vy * dt
        domet[i][j] = x / np.cos(beta[i])
        
plt.figure(1)
plt.contourf(np.rad2deg(alfa), np.rad2deg(beta), domet, 20, cmap = cm.jet)
plt.xlabel('Alfa [deg]')
plt.ylabel('Beta [deg]')
plt.colorbar()
plt.show()