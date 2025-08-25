#Odrediti domet hica koji se nad padinom pod uglom beta lansira početnom brzinom v0 i pod uglom alfa
#i prikazati putanju tela i padinu

import numpy as np
import matplotlib.pyplot as plt

g = -9.81
beta = np.deg2rad(-30)
alfa = np.deg2rad(50)
v = 300
dt = 1e-3

x = [0]
y = [0]
vx = v * np.cos(alfa)
vy = v * np.sin(alfa)

while x[-1] == 0 or y[-1] / x[-1] > np.tan(beta):
    vy += g * dt
    #vx = const
    x.append(x[-1] + vx * dt)
    y.append(y[-1] + vy * dt)
    
domet = x[-1] / np.cos(beta)
print(domet)

#Pretvorimo liste u nizove zbog plotovanja
x = np.array(x)
y = np.array(y)

padina = x * np.tan(beta)

plt.figure(1)
plt.plot(x, y, 'r') #putanja
plt.plot(x, padina, linewidth = 3) #padina
plt.show()