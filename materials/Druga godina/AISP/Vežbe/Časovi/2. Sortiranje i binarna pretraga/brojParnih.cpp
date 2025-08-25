// Dat je niz celih brojeva dužine n. Koliko brojeva se u nizu
// pojavljuje paran broj puta?

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];

    sort(begin(niz), end(niz));

    int brParnih = 0, duzina = 1;
    for(int i = 1; i < n; i++) {
        if(niz[i] == niz[i - 1])
            duzina++;
        else {
            if(duzina % 2 == 0)
                brParnih++;
            duzina = 1;
        }
    }
    if(duzina % 2 == 0)
        brParnih++;
    cout << brParnih << endl;
    return 0;
}