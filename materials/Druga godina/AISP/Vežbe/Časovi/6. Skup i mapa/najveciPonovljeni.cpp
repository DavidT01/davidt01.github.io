// https://petlja.org/biblioteka/r/Zbirka2/najveci_duplikat1

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n, x, rez = 0; cin >> n;
    set<int> s;
    while(n--) {
        cin >> x;
        if(s.find(x) != end(s) && x > rez)
            rez = x;
        else
            s.insert(x);
    }
    if(rez > 0)
        cout << rez << endl;
    else
        cout << "nema" << endl;
    return 0;
}