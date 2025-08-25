# Otvaramo fajl za čitanje i ispisujemo linije, with govori da treba zatvoriti fajl
# On sam po sebi ne obrađuje izuzetke, pa se često kombinuje sa try blokom
try:
    with open('1.txt', 'r') as f:
        for line in f:
            print(line)
except IOError:
    pass

# Otvaramo fajl i za pisanje i za čitanje, dopisujemo na kraj fajla, vraćamo se na početak i čitamo linije
with open('1.txt', 'a+') as g:
    g.write('\nmarmunee\n')
    g.seek(0, 0)
    print(g.readlines())
    
import json

# Učitavamo JSON podatke i prebacujemo ih u objekat - deserijalizacija
with open('1.json', 'r') as f:
    obj = json.load(f)
    print(obj)
    print(obj["Ime"])

# Objekat prebacujemo u JSON - serijalizacija
with open('2.json', 'w') as g:
    json.dump(obj, g)
    
# Funkcije loads i dumps prebacuju u string umesto u fajl

# Ako imamo klasu A, rečnik od nje pravimo pomoću A().__dict__