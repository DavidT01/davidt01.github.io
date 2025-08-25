#Kojom brzinom i pod kojim uglom treba ispaliti hitac da bi pogodio telo A

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
H = 100
d = 15
dt = 1e-3
Alfa =  np.deg2rad(np.arange(70, 95, 5))
V0 = np.arange(10, 40, 5)
R = [[[] for column in range(len(Alfa))] for row in range(len(V0))]

for i, v0 in enumerate(V0):
    for j, alfa in enumerate(Alfa):
        #Kosi hitac
        x1 = 0
        y1 = 0
        vx = v0 * np.cos(alfa)
        vy = v0 * np.sin(alfa)
        #Slobodan pad
        x2 = d
        y2 = H
        v = 0
        while x1 < d and y2 >= 0 and y1 >= 0:
            #Kosi hitac
            vy += g * dt
            x1 += vx * dt
            y1 += vy * dt
            #Slobodan pad
            v += g * dt
            y2 += v * dt
        R[i][j].append(np.sqrt((x1 - x2)**2 + (y1 - y2)**2))

R = np.array([np.array(i) for i in R]) #pravi matricu od ugnježdene liste
resenje = np.where(R == np.amin(R)) #minimalna vrednost

print('Optimalna brzina =', V0[resenje[0][0]], 'm/s', '\nOptimalni ugao =', np.rad2deg(Alfa[resenje[0][0]]), 'deg')