// https://petlja.org/biblioteka/r/Zbirka2/sve_sortirane_particije

#include <iostream>
#include <vector>

using namespace std;

void particije(int n, int maxSabirak, vector<int>& particija) {
    if(n == 0) {
        for(int x : particija)
            cout << x << ' ';
        cout << endl;
        return;
    }
    for(int sabirak = 1; sabirak <= maxSabirak; sabirak++) {
        particija.push_back(sabirak);
        particije(n - sabirak, min(n, sabirak), particija);
        particija.pop_back();
    }
}

int main() {
    int n; cin >> n;
    vector<int> particija;
    particije(n, n, particija);
    return 0;
}