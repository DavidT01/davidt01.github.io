#Odrediti pod kojim uglom će hitac udariti u Zemlju i kako ovaj ugao zavisi od uglova alfa i beta

import numpy as np
import matplotlib.pyplot as plt

from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

g = -9.81
beta = np.deg2rad(np.arange(-30, 0))
alfa = np.deg2rad(np.arange(0, 50))
v = 300
dt = 1e-1
ugao = np.zeros([len(beta), len(alfa)])

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
        ugao[i][j] = np.abs(np.arctan(vy / vx) - beta[i])
        
#3D plotovanje
figure = plt.figure(1)
ax = figure.add_subplot(1, 1, 1, projection = '3d')
alfa, beta = np.meshgrid(alfa, beta)
ax.plot_surface(np.rad2deg(alfa), np.rad2deg(beta), np.rad2deg(ugao), cmap = cm.jet, linewidth = 0, antialiased = False)
ax.set_xlabel('Alfa [deg]')
ax.set_ylabel('Beta [deg]')
ax.set_zlabel('Ugao [deg]')
plt.show()