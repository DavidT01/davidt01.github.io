#Odrediti kojom brzinom će ovo telo udariti o tlo

g = -9.81
v = 100
h = 0
dt = 1e-3

while h >= 0:
    h += v * dt
    v += g * dt
    
print(v)