#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> niz(n), parcijalneSume(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];
    map<int, int> mapaSuma;
    parcijalneSume[0] = niz[n - 1];
    mapaSuma[parcijalneSume[0]] = n - 1;
    for(int i = 1; i < n; i++) {
        parcijalneSume[i] = niz[n - i - 1] + parcijalneSume[i - 1];
        mapaSuma[parcijalneSume[i]] = n - i - 1;
    }
    int najveca_suma = 0, trenutna_suma = 0;
    for(int i = 0; i < n; i++) {
        trenutna_suma += niz[i];
        if(mapaSuma.find(trenutna_suma) != mapaSuma.end())
            if(mapaSuma[trenutna_suma] > i)
                if(najveca_suma < trenutna_suma)
                    najveca_suma = trenutna_suma;
    }
    cout << najveca_suma;
    return 0;
}