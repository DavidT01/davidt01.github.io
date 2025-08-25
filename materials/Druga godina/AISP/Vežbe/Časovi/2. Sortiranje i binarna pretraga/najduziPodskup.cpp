// https://petlja.org/biblioteka/r/Zbirka2/najduzi_podskup_uzastopnih

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

main() {
    int n; cin >> n;
    vector<int> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];

    // sortiramo i uklonimo duplikate

    sort(begin(niz), end(niz));
    auto it = unique(begin(niz), end(niz));
    niz.erase(it, end(niz));
    n = niz.size();

    int pocetak = 0, duzina = 1, maxPocetak = 0, maxDuzina = 1;
    for(int i = 1; i < n; i++)
        if(niz[i] == niz[i - 1] + 1) {
            duzina++;
            if(duzina > maxDuzina) {
                maxDuzina = duzina;
                maxPocetak = pocetak;
            }
        }
        else {
            duzina = 1;
            pocetak = i;
        }
    for(int i = maxPocetak; i < maxPocetak + maxDuzina; i++)
        cout << niz[i] << endl;
    return 0;
}