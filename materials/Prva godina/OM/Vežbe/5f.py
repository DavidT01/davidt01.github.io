#Odrediti kojom brzinom će ovo telo udariti u tlo

gamaM = 3.983324e14
R = 6.371e6
v = 300
dt = 1e-4
r = R

while r >= R: #dok telo na udari o tlo
    v -= gamaM / r**2 * dt
    r += v * dt
    
print(v)