// Opisati realizaciju apstraktne strukture podataka koja podržava
// sledeće operacije:
// • umetni(x): umetni ključ x u strukturu podataka, ako ga tamo već nema;
// • obriši(x): obriši ključ x iz strukture podataka (ako ga ima);
// • naredni(x): pronađi najmanji ključ u strukturi podataka koji je strogo
// veći od x. Izvršavanje svake od ovih operacija treba da ima vremensku
// složenost O(log k) u najgorem slučaju, gde je k broj elemenata u strukturi
// podataka.

#include <iostream>
#include <set>

using namespace std;

set<int> s;

void dodaj(int x) {
    s.insert(x);
}

void obrisi(int x) {
    s.erase(x);
}

int najblizi(int x) {
    auto it = s.lower_bound(x);
    if(it == end(s))
        return *(--it);
    if(it == begin(s))
        return *it;
    int a = *it;
    int b = *(--it);
    if(abs(a - x) < abs(b - x))
        return a;
    return b;
}

int main() {
    return 0;
}