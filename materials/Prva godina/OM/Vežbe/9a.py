#Odrediti do koje visine će se popeti telo koje je brzinom v0 bačeno sa Zemlje vertikalno u vis,
#ako na njega deluje sila obrnuto srazmerna kvadratu rastojanja od centra Zemlje korišćenjem konstantnog vremenskog koraka ∆t,
#kao i korišćenjem koraka koji je funkcija ubrzanja tela dat kao C/a, gde je a ubrzanje tela usled Zemljine gravitacije, 
#a C konstanta takva da u početnom trenutku vremeski korak bude ∆t, a zatim odrediti relativnu grešku svake visine u odnosu
#na analitičku za datu zavisnost ubrzanja, kao i vremena izvršavanja kodova i njihov odnos

import numpy as np
import time

GM = 3.983324e14
R = 6.371e6
V = 10000
dt = 1e-2

#Analitičko rešenje
Ha = V**2 * R**2 / (2 * GM - R * V**2)

#dt = const
pocetak1 = time.time()
v = V
r = R
while v >= 0:
    v -= GM / r**2 * dt
    r += v * dt
h1 = r - R
vreme1 = time.time() - pocetak1
print('dt = const; h =', h1 / 1000, 'km;', 'vreme izvršavanja:', vreme1, 's')

#dt != const
pocetak2 = time.time()
v = V
r = R
c = GM * dt / R**2
while v >= 0:
    DT = c * r**2 / GM
    v -= GM / r**2 * DT
    r += v * DT
h2 = r - R
vreme2 = time.time() - pocetak2
print('dt != const; h =', h2 / 1000, 'km;', 'vreme izvršavanja:', vreme2, 's')

#Relativne greške
print('dt = const; relativna greška:', abs(h1 - Ha) * 100 / Ha, '%')
print('dt != const; relativna greška:', abs(h2 - Ha) * 100 / Ha, '%')

#Odnos vremena izvršavanja
print('Odnos izvršavanja kodova:', vreme2/vreme1)