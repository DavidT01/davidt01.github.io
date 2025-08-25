#Odrediti do koje visine će se popeti telo koje je brzinom v0 bačeno sa Zemlje vertikalno u vis, 
#ako na njega deluje sila obrnuto srazmerna kvadratu rastojanja od centra Zemlje: 
#F = gama * (m * M) / r^2; gama = 6.67 * 10^(-11) m^3/kg*s^2 - gravitacione konstanta, M = 5.972 * 10^24 kg - masa Zemlje, 
#R = 6.371 * 10^6 m - poluprečnik Zemlje, r - rastojanje od centra Zemlje, m - masa tela

gamaM = 3.983324e14 #gama * M
R = 6.371e6
v = 3000
dt = 1e-3
r = R #telo je bačeno sa površine Zemlje

while v > 0:
    v -= gamaM / r**2 * dt #v = a * dt = F / m * dt = gama * M / r^2 * dt
    r += v * dt
    
print((r - R) / 1000, "km") #postignuta visina u km