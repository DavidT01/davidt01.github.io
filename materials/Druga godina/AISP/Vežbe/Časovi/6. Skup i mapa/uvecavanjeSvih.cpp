// Konstruisati apstraktnu strukturu podataka za čuvanje preslikavanja
// ključeva u vrednosti. Struktura podataka treba da podržava sledeće operacije:
// • vrednost(x): vraća vrednost pridruženu elementu sa ključem x (nula, ako ključ x nema pridruženu vrednost);
// • dodaj(x, y): ključu x pridruži vrednost y;
// • obriši(x): obriši element sa ključem x;
// • uvećaj(x, y): vrednost pridruženu ključu x uvećaj za y;
// • uvećajSve(y): vrednosti pridružene svim ključevima uvećaj za y.

#include <iostream>
#include <map>

using namespace std;

map<int, int> m;
int uvecanje = 0;

int vrednost(int x) {
    return m[x] + uvecanje;
}

void dodaj(int x, int y) {
    m[x] = y - uvecanje;
}

void obrisi(int x) {
    m.erase(x);
}

void uvecaj(int x, int y) {
    m[x] += y;
}

void uvecajSve(int y) {
    uvecanje += y;
}

int main() {
    return 0;
}