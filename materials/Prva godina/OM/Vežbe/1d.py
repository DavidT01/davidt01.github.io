#Prikazati položaj tela u ekvidistantnim trenucima vremena i odrediti odnos razlika u visinama za
#susedne vremenske trenutke

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
h = 1000
v = 0
t = 0
dt = 1e-4
H = []

while h > 0: 
    h += v * dt
    v += g * dt
    t += dt
    H.append(h)

plt.figure(1)
plt.plot(np.zeros_like(H), H, '.r')
plt.show()

razlike = np.diff(H)
print(razlike)