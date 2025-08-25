// https://petlja.org/biblioteka/r/Zbirka2/sume_segmenata

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> zarade(n);
    for(int i = 0; i < n; i++)
        cin >> zarade[i];

    // prefiksne sume, n + 1
    vector<int> ps(n + 1);
    for(int i = 1; i <= n; i++)
        ps[i] = ps[i - 1] + zarade[i - 1];

    // funkcija koja računa prefiksne sume, iz zaglavlja numeric
    vector<int> prefSum(n + 1);
    partial_sum(begin(zarade), end(zarade), begin(prefSum) + 1);

    int m;
    cin >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        cout << ps[b + 1] - ps[a] << endl;
    }
    return 0;
}