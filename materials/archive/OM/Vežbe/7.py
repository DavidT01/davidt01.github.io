#Jedan hitac je ispaljen brzinom v0 pod uglom alfa, dok je drugi sa rastojanja d ispaljen u istom trenutku prema
#prvom. Kojom brzinom i pod kojim uglom je potrebno ispaliti drugi hitac tako da na rastojanju d1 pogodi prvi hitac?
#Prikazati putanje do trenutka sudara

import numpy as np
import matplotlib.pyplot as plt

from sympy import *

alfa = np.deg2rad(30)
v1 = 100
g = 9.81
d = 1000
d1 = 700

v2 = Symbol('v2')
beta = Symbol('beta')
t = Symbol('t')

x1 = v1 * cos(alfa) * t
y1 = -1/2 * g * t**2 + v1 * sin(alfa) * t
x2 = d - v2 * cos(beta) * t
y2 = -1/2 * g * t**2 + v2 * sin(beta) * t

tau = float(solve(x1 - d1, t)[0]) #Prva vrednost je funkcija kojoj se traži nula, po promenljivoj koja je drugi argument

h1 = y1.subs({t:tau}) #Menja vrednost tau u promenljivu t kod funkcije y1
resenje = solve([(x2 - d1).subs({t:tau}), (y2 - h1).subs({t:tau})])[0] #Uzimamo pozitivno rešenje

print(resenje)

#Računanje putanja
BETA = float(resenje[beta])
V2 = float(resenje[v2])
T = np.linspace(0, tau, 1000)
X1 = np.zeros_like(T)
Y1 = np.zeros_like(T)
X2 = np.zeros_like(T)
Y2 = np.zeros_like(T)

for i, dt in enumerate(T):
    X1[i] = x1.subs({t:dt})
    Y1[i] = y1.subs({t:dt})
    X2[i] = x2.subs({t:dt, beta:BETA, v2:V2})
    Y2[i] = y2.subs({t:dt, beta:BETA, v2:V2})

#Plotovanje putanja
plt.figure(1)
plt.plot(X1, Y1, 'r')
plt.plot(X2, Y2)
plt.show()