// https://petlja.org/biblioteka/r/Zbirka2/provera_permutacija1

#include <iostream>
#include <set>

using namespace std;

int main() {
    int n, m, x;
    cin >> n;
    multiset<int> a;
    for(int i = 0; i < n; i++) {
        cin >> x;
        a.insert(x);
    }
    cin >> m;
    if(m != n)
        cout << "ne" << endl;
    else {
        multiset<int> b;
        while(m--) {
            cin >> x;
            b.insert(x);
        }
        cout << (a == b ? "da" : "ne") << endl;
    }
    return 0;
}