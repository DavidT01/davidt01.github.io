// https://petlja.org/biblioteka/r/Zbirka2/ruter

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Zi = Z(i - 1) + Li - Di
    // Li = a0 + . . . + a(i - 1) = L(i - 1) + a(i - 1)
    // Di = ai + . . . + a(n - 1) = D(i - 1) - a(i - 1)
    // Z0 = 0*a0 + 1*a1 + . . . + (n - 1)*a(n - 1)
    // L0 = 0, D0 = a0 + a1 + . . . + a(n - 1)
    int n; cin >> n;
    vector<int> a(n);
    uint64_t Z = 0, L = 0, D = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        Z += i * a[i];
        D += a[i];
    }

    uint64_t minDuzina = Z;
    for(int i = 1; i < n; i++) {
        L += a[i - 1];
        D -= a[i - 1];
        Z += L - D;
        if(Z < minDuzina)
            minDuzina = Z;
    }
    cout << minDuzina << endl;
    return 0;
}