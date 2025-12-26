#Telo A slobodno pada sa visine H na rastojanju d. Iz koordinatnog početka u istom trenutku
#ispaljuje se kosi hitac. Odrediti ugao i početnu brzinu kojom je neophodno lansirati drugo telo
#da bi se ono susrelo sa telom A Ojler-Kromerovom metodom i prikazati putanje tela

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
H = 100
d = 15
dt = 1e-3

#Analitičko rešenje
alfa = np.arctan(H / d)
v0min = np.sqrt(9.81 * H / (2 * np.sin(alfa)**2)) #v0 je u intervalu [v0min, beskonačno]

#Kosi hitac
x1 = 0
y1 = 0
vx = v0min * np.cos(alfa)
vy = v0min * np.sin(alfa)
X1 = []
Y1 =[]
#Slobodan pad
x2 = d
y2 = H
v = 0
X2 = []
Y2 = []

while x1 < d and y2 >= 0 and y1 >= 0:
    #Kosi hitac
    vy += g * dt
    x1 += vx * dt
    y1 += vy * dt
    #Slobodan pad
    v += g * dt
    y2 += v * dt
    X1.append(x1)
    Y1.append(y1)
    X2.append(x2)
    Y2.append(y2)
    
plt.figure(1)
plt.plot(X1, Y1, 'r')
plt.plot(X2, Y2)
plt.show()