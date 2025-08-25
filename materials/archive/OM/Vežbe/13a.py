#Primenom OK metode odrediti kojom brzinom telo mase 250kg koje slobodno pada sa visina iz skupa
#{100, 110, 120, ..., 10000} udara u Zemlju u slučaju da na njega deluje samo homogeno polje
#Zemljine gravitacije i u slučaju da na njega deluje i sila otpora Fo = -1/2 * CS * ro * v^2,
#gde je ubrzanje usled aerodinamičkog otpora ao = -1/2 * ro * v^2 / BC (BC je balistički koeficijent,
#BC = m / CS). Uzeti i da gustina atmosfere opada sa visinom prema eksponencijalnom zakonu: ro = ro0 * e^(-h/H).
#Prikazati zavisnost brzine udara o tlo od visine u oba slučaja

import numpy as np
import matplotlib.pyplot as plt

g = 9.81
m = 250
ro0 = 1.23
Hh = 10000
CS = 0.5
BC = m / CS #balistički koeficijent
H = np.arange(100, 10010, 10)
V = np.zeros_like(H) #bez otpora
Vo = np.zeros_like(H) #sa otporom
dt = 1e-1

for i, h1 in enumerate(H):
    #Bez otpora
    h = h1
    v = 0
    while h >= 0:
        v += g * dt
        h -= v * dt
    V[i] = v
    #Sa otporom
    h = h1
    v = 0
    while h >= 0:
        ro = ro0 * np.exp(- h / Hh)
        a0 = -0.5 * ro * v**2 / BC
        v += (g + a0) * dt
        h -= v * dt
    Vo[i] = v
    
plt.figure(1)
plt.plot(H, V, 'r', label = 'Bez otpora')
plt.plot(H, Vo, label = 'Sa otporom')
plt.xlabel('Visina [m]')
plt.ylabel('Brzina udara [m/s]')
plt.legend()
plt.grid()
plt.show()