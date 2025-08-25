#Prikazati putanje za različite početne brzine i uglove

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
H = 100
d = 15
dt = 1e-3
Alfa =  np.deg2rad(np.arange(70, 95, 5))
V0 = np.arange(10, 35, 5)

#Ugnježdene liste
X1 = [[[] for column in range(len(Alfa))] for row in range(len(V0))]
Y1 =[[[] for column in range(len(Alfa))] for row in range(len(V0))]
X2 = [[[] for column in range(len(Alfa))] for row in range(len(V0))]
Y2 = [[[] for column in range(len(Alfa))] for row in range(len(V0))]

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
            X1[i][j].append(x1)
            Y1[i][j].append(y1)
            X2[i][j].append(x2)
            Y2[i][j].append(y2)
        
figure = plt.figure(figsize = (14, 12), layout = 'constrained') #Svaki grafik ima svoj prostor
for i in range(len(V0)):
    for j in range(len(Alfa)):
        ax = figure.add_subplot(len(V0), len(Alfa), len(Alfa) * i + j + 1)
        ax.plot(X1[i][j], Y1[i][j], '.')
        ax.plot(X2[i][j], Y2[i][j], '.r')
        vplt = V0[i]
        alfaplt = np.rad2deg(Alfa[j])
        ax.set_title(f'brzina = {vplt}, ugao = {alfaplt}')
plt.show()