// Pronaći koliko nepraznih segmenata nekog niza daje traženi zbir

#include <iostream>
#include <map>

using namespace std;

int main() {
    int z, n, x; cin >> z >> n;
    map<int, int> mapa;
    mapa[0] = 1;
    int suma = 0, brSegmenata = 0;
    while(n--) {
        cin >> x;
        suma += x;
        brSegmenata += mapa[suma - z];
        mapa[suma]++;
    }
    cout << brSegmenata << endl;
    return 0;
}