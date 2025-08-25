// https://petlja.org/biblioteka/r/Zbirka2/broj_parova_datog_zbira2

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

    int brParova = 0, i = 0, j = n - 1;
    while(i < j)
        if(niz[i] + niz[j] < s)
            i++;
        else if(niz[i] + niz[j] > s)
            j--;
        else {
            i++;
            j--;
            brParova++;
        }
    cout << brParova << endl;
    return 0;
}