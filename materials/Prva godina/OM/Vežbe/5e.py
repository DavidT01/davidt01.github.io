#Odrediti do koje početne brzine je razlika u visini dobijena Ojler-Kromerovom metodom manja od 1% u odnosu na analitički dobijenu

import numpy as np

gamaM = 3.983324e14
R = 6.371e6
g = 9.81
dt = 1e-2
V = np.arange(20, 1500, 1)
H = []

#Analitičko rešenje:
visine = V**2 / (2 * g)

for i, v in enumerate(V):
    r = R
    while v > 0:
        v -= gamaM / r**2 * dt
        r += v * dt
    H.append(r - R)
    if(abs(visine[i] - H[i]) / H[i] >= 0.01):
        break
    
print(V[i])