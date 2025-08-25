#Primenom OK metode odrediti domet i maksimalnu visinu kosog hica koji je ispaljen brzinom
#od 100 m/s pod uglom od 45 stepeni ako na njega deluje samo homogeno polje Zemljine teže
#i ako na njega deluje sila otpora vazduha čiji je intenzitet F = -1/2 * C * S * ro * v^2,
#gde je C koeficijent otpora, S referentna površina tela, a ro gustina atmosfere. Uzeti da je 
#C * S = 0.001, a masa tela 1 kilogram. Prikazati putanje, domete i maksimalne dostignute visine

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
CS = 0.001
ro = 1.23
m = 1
v0 = 100
alfa = np.deg2rad(45)
dt = 1e-2

#Bez otpora
X = []
Y = []
x = 0
y = 0
vx = v0 * np.cos(alfa)
vy = v0 * np.sin(alfa)
while y >= 0:
    vy -= g*dt
    x += vx * dt
    y += vy *dt
    X.append(x)
    Y.append(y)

#Sa otporom
Xo = []
Yo = []
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
    Xo.append(xo)
    Yo.append(yo)

#Pretvaranje u niz kako bi lako našli visine i domete
X = np.array(X)
Y = np.array(Y)   
Xo = np.array(Xo)   
Yo = np.array(Yo)

H = np.amax(Y)
D = X[-1]
Ho = np.amax(Yo)
Do = Xo[-1]

#Putanje, visine i dometi
plt.figure(1)
plt.plot(X, Y, 'b')
plt.plot(X[np.argwhere(Y == H)], H, 'ob')
plt.plot(D, Y[-1], 'ob')
plt.plot(Xo, Yo, 'r')
plt.plot(Xo[np.argwhere(Yo == Ho)], Ho, 'or')
plt.plot(Do, Yo[-1], 'or')
plt.grid()
plt.show()