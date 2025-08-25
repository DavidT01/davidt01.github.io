// https://arena.petlja.org/competition/asp-rokovi-1#tab_135202

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct stablo {

    long long x_poc, x_kraj, visina;
    
};

long long kolicina(long long x, const vector<stablo>& stabla) {

    long long rezultat = 0;
    for (const stablo& s : stabla) {
        long long duzina = max(s.x_kraj - max(x, s.x_poc), 0ll);
        rezultat += duzina * s.visina;
    }

    return rezultat;

}

int main() {

    long long t; cin >> t;
    int n; cin >> n;
    vector<stablo> stabla(n);
    for (int i = 0; i < n; i++)
    cin >> stabla[i].x_poc >> stabla[i].x_kraj >> stabla[i].visina;

    long long x_max = 0;
    for (int i = 0; i < n; i++)
    x_max = max(x_max, stabla[i].x_kraj);

    long long levo = 0, desno = x_max;
    while (levo <= desno) {
        long long sredina = levo + (desno - levo) / 2;
        if (kolicina(sredina, stabla) <= t)
            desno = sredina - 1;
        else
            levo = sredina + 1;
    }

    cout << levo << ' ' << kolicina(levo, stabla) << endl;

    return 0;

}