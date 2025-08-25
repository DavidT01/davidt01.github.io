#Odrediti putanju veštačkog Zemljinog satelita koji je lansiran sa visine od h = 200 km horizontalnom
#brzinom od v0 = sqrt(gama * M / (R + h)) ≈ 7.78 km/s, uzimajući u obzir gravitaciono polje Zemlje, kao i otpor
#atmosfere F = -1/2 * Co * S * ro * v^2, pri čemu važi ro = ro0 * e^(-h / H). Balistički koeficijent (BC = m / Co*S) 
#letelice je 250 kg/m2, gustina atmosfere na površini Zemlje ro0 = 1.2255 kg/m3 , a skala visina H = 8.5km

#a) Koliki će biti životni vek ovog satelita?
#b) Kako mu se menjaju brzina i visina sa vremenom?
#c) Šta se dešava sa životnim vekom ako se gustina atmosfere udvostruči?
#d) Kako se menja moment količine kretanja u odnosu na geocentar?
#e) Kako se menja ukupna mehanička energija letelice?

import numpy as np
import matplotlib.pyplot as plt

M = 5.972e24
R = 6.378e6
dan = 3600*24
gama = 6.67e-11
ro0 = 1.2255
H = 8500
BC = 250
h = 2e5
v0 = np.sqrt(gama * M / (R + h))

x = [R + h]
y = [0]
vx = [0]
vy = [v0]
L = [np.cross([x[-1], y[-1]], [vx[-1], vy[-1]])]
Ek = (vx[-1]**2 + vy[-1]**2) / 2
Ep = -gama * M / (x[-1]**2 + y[-1]**2)**0.5
E = [Ek + Ep]
T = [0]
t = 0
dt = 1

while h > 0:
    h = (x[-1]**2 + y[-1]**2)**0.5 - R
    ro = ro0 * np.exp(-h / H)
    v = (vx[-1]**2 + vy[-1]**2)**0.5
    ax = -gama * M / (x[-1]**2 + y[-1]**2)**(3 / 2) * x[-1] - ro / 2 / BC * v * vx[-1]
    ay = -gama * M / (x[-1]**2 + y[-1]**2)**(3 / 2) * y[-1] - ro / 2 / BC * v * vy[-1]
    vx.append(vx[-1] + ax * dt)
    vy.append(vy[-1] + ay * dt)
    x.append(x[-1] + vx[-1] * dt)
    y.append(y[-1] + vy[-1] * dt)
    L.append(np.cross([x[-1], y[-1]], [vx[-1], vy[-1]]))
    Ek = (vx[-1]**2 + vy[-1]**2) / 2
    Ep = -gama * M / (x[-1]**2 + y[-1]**2)**0.5
    E.append(Ek + Ep)
    t += dt
    T.append(t / dan)
    
x = np.array(x)
y = np.array(y)
vx = np.array(vx)
vy = np.array(vy)
v=np.sqrt(vx**2 + vy**2)
h=np.sqrt(x**2 + y**2) - R
L=np.array(L)
E=np.array(E)

#Putanja letelice
plt.figure(1)
plt.title('Putanja letelice')
plt.plot(x / R, y / R)
#a)
print(f'Zivotni vek letelice je {t / dan} dana.')
#b)
plt.figure(2)
plt.title('Brzina i visina tokom vremena')
plt.plot(T, v, 'b', label = 'Zavisnost brzine')
plt.plot(T, h, 'r', label = 'Zavisnost visine')
plt.grid()
#c)
print("Ako se gustina atmosfere udvostruci, zivotni vek se proporcionalno smanji.")
#d)
plt.figure(3)
plt.title('Moment količine kretanja tokom vremena')
plt.plot(T, L, 'b')
plt.grid()
#e)
plt.figure(4)
plt.title('Ukupna mehanička energija letelice tokom vremena')
plt.plot(T, E, 'b')
plt.grid()
plt.show()