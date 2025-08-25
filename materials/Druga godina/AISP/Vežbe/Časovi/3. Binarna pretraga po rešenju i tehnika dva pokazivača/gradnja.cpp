// https://petlja.org/biblioteka/r/Zbirka2/gradnja

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool ispitajRastojanje(int x, int m, vector<int>& lokacije, int n) {
    m--;
    int poslednjaLokacija = lokacije[0];
    for(int i = 1; i < n && m > 0; i++)
        if(lokacije[i] - poslednjaLokacija >= x) {
            m--;
            poslednjaLokacija = lokacije[i];
        }
    return m == 0;
}

int main() {
    int m, n; cin >> m >> n;
    vector<int> lokacije(n);
    for(int i = 0; i < n; i++)
        cin >> lokacije[i];

    sort(begin(lokacije), end(lokacije));

    int l = 1, d = lokacije[n - 1], resenje = 1;
    while(l <= d) {
        int s = (d + l) / 2;
        if(ispitajRastojanje(s, m, lokacije, n)) {
            resenje = s;
            l = s + 1;
        }
        else
            d = s - 1;
    }
    cout << resenje << endl;
    // ili d ili l - 1
    return 0;
}