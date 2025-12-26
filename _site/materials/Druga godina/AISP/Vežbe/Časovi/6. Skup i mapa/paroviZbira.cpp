// https://petlja.org/biblioteka/r/Zbirka2/broj_parova_datog_zbira1

#include <iostream>
#include <set>

using namespace std;

int main() {
    int s, n, x;
    cin >> s >> n;
    set<int> brojevi;
    int brParova = 0;
    while(n--) {
        cin >> x;
        if(brojevi.find(s - x) != end(brojevi))
            brParova++;
        brojevi.insert(x);
    }
    cout << brParova << endl;
    return 0;
}