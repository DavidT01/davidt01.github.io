// https://petlja.org/biblioteka/r/Zbirka2/suma_posle_ciklicnog_pomeranja

#include <iostream>
#include <vector>

#define M 1234567

using namespace std;

int zbir(int a, int b) {
    return ((a % M) + (b % M)) % M;
}

int razlika(int a, int b) {
    return (M + (a % M) - (b % M)) % M;
}

int proizvod(int a, int b) {
    return ((a % M) * (b % M)) % M;
}

int main() {
    int n; cin >> n;
    vector<int> niz(n);
    int Z = 0;
    int Zi = 0;
    for(int i = 0; i < n; i++) {
        cin >> niz[i];
        Z = zbir(Z, niz[i]);
        Zi = zbir(Zi, proizvod(i, niz[i]));
    }

    // Z(i) = Z(i-1) - Z + n * a(i - 1)
    int maxZbir = Zi;
    int maxI = 0;
    for(int i = 1; i < n; i++) {
        Zi = razlika(zbir(Zi, proizvod(n, niz[i - 1])), Z);
        if(Zi > maxZbir) {
            maxZbir = Zi;
            maxI = i;
        }
    }
    cout << maxZbir << endl;
    return 0;
}