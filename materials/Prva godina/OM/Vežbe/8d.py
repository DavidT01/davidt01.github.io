#Na koji način optimalni ugao, brzina pogotka i visina pogotka zavise od početne brzine

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
H = 500
d = 1000
dt = 1e-3
Alfa = np.deg2rad(np.arange(60, 95, 5))
V0 = np.arange(100, 1000, 100)
alfa_optimalno = np.zeros_like(V0)
brzina_pogotka = np.zeros_like(V0)
visina_pogotka = np.zeros_like(V0)

for i in range(len(V0)):
    razlika_visina = np.zeros_like(Alfa)
    v_pogotka = np.zeros_like(Alfa)
    h_pogotka = np.zeros_like(Alfa)
    for j in range(len(Alfa)):
        #Kosi hitac
        x1 = 0
        y1 = 0
        vx = V0[i] * np.cos(Alfa[j])
        vy = V0[i] * np.sin(Alfa[j])
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
        razlika_visina[j] = np.abs(y1 - y2)
        v_pogotka[j] = np.sqrt(vx**2 + vy**2)
        h_pogotka[j] = y2
    alfa_optimalno[i] = Alfa[np.argmin(razlika_visina)] #argmin vraća poziciju minimalnog elementa
    brzina_pogotka[i] = v_pogotka[np.argmin(razlika_visina)]
    visina_pogotka[i] = h_pogotka[np.argmin(razlika_visina)]
    
plt.figure(1)
plt.plot(V0, np.rad2deg(alfa_optimalno))
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Ugao [deg]')

plt.figure(2)
plt.plot(V0, brzina_pogotka)
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Brzina pogotka [m/s]')

plt.figure(3)
plt.plot(V0, visina_pogotka)
plt.xlabel('Početna brzina [m/s]')
plt.ylabel('Visina pogotka [m]')
plt.show()