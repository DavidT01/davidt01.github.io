// https://petlja.org/biblioteka/r/Zbirka2/broj_parova_datog_zbira

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int s, n; cin >> s >> n;
    vector<int> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];

    sort(begin(niz), end(niz));

    int brojParova = 0;
    for(int i = 0; i < n; i++)
        if(binary_search(begin(niz), begin(niz) + i, s - niz[i]))
            brojParova++;
    cout << brojParova << endl;
    return 0;
}