#Odrediti do koje visine će se popeti telo koje je brzinom v0 bačeno sa Zemlje vertikalno u vis, kao i vreme penjanja

g = -9.81
v = 100
h = 0
t = 0
dt = 1e-3

while v >= 0:
    h += v * dt
    v += g * dt
    t += dt
    
print(h, t)