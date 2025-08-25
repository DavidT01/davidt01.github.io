#include <iostream>
#include <vector>

using namespace std;

void zagrade(vector<string>& sveKombinacije, string kombinacija, int otvorene, int zatvorene, int td, int d, int n) {
    if(kombinacija.length() == n) {
        if(td == 0)
            sveKombinacije.push_back(kombinacija);
        return;
    }
    if(otvorene < n / 2 && td < d)
        zagrade(sveKombinacije, kombinacija + '(', otvorene + 1, zatvorene, td + 1, d, n);
    if(zatvorene < otvorene)
        zagrade(sveKombinacije, kombinacija + ')', otvorene, zatvorene + 1, td - 1, d, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, d;
    cin >> n >> d;
    vector<string> sveKombinacije;
    zagrade(sveKombinacije, "", 0, 0, 0, d, n);
    for(string kombinacija : sveKombinacije)
        cout << kombinacija << endl;
    return 0;
}