#Nakon koliko vremena i na kojoj visini je razlika između asimptotske brzine i one 
#dobijene OK metodom manja od 1%

import numpy as np

g = 9.81
k = 0.17658
H = 2000
dt = 1e-2
t = 0
v = 0

#Asimptotska brzina
va = g / k

while H >= 0:
    v += (g - k * v) * dt
    H -= v * dt
    t += dt
    if(abs(va - v) / va <= 0.01):
        print('Vreme =', t, 's\nVisina =', H, 'm')
        break