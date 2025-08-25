#Odrediti brzinu kojom telo udara o tlo i vreme trajanja pada pri slobodnom padu sa proizvoljne visine

g = -9.81
h = 1000
v = 0
t = 0
dt = 1e-5

while h > 0:
    h += v * dt
    v += g * dt
    t += dt
    
print(v, t)