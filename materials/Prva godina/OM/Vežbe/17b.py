#Kako se menja moment količine kretanja letelice u odnosu na heliocentar?
#Uzeti početnu brzinu 10 km/s i konstantan vremenski trenutak

import numpy as np
import matplotlib.pyplot as plt

Ms = 1.989e30
Rz = 6.378e6
gama = 6.67e-11
AJ = 1.496e11
T = 365.25 * 24 * 60 * 60 #julijanska godina
vorb = 2 * np.pi * AJ / T
v0 = 1e3
dt = 1000
L = [np.cross([AJ, 0], [0, vorb + v0])] #moment impulsa, L = r x v

x = [AJ]
y = [0]
vx = [0]
vy = [vorb + v0]
t = 0
while t < T:
    ax = -gama * Ms / (x[-1]**2 + y[-1]**2)**(3/2) * x[-1]
    ay = -gama * Ms / (x[-1]**2 + y[-1]**2)**(3/2) * y[-1]
    vx.append(vx[-1] + ax * dt)
    vy.append(vy[-1] + ay * dt)
    x.append(x[-1] + vx[-1] * dt)
    y.append(y[-1] + vy[-1] * dt)
    L.append(np.cross([x[-1], y[-1]], [vx[-1], vy[-1]]))
    t += dt
    
L = np.array(L)
print(L)