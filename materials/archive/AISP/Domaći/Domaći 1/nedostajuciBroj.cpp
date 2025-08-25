#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> niz(n), nizRaz(n);
    for(int i = 0; i < n; i++){
        cin >> niz[i];
        nizRaz[i + 1] = niz[i] - (i + 1);
    }
    int m; cin >> m;
    for(int i = 0; i < m; i++)
    {
        int k; cin >> k;
        if(k > nizRaz[n])
            cout << niz[n - 1] + (k - nizRaz[n]) << endl;
        else {
            auto it = lower_bound(nizRaz.begin(), nizRaz.end(), k);
            int l = *it;
            int pozicija = it - nizRaz.begin();
            cout << niz[pozicija - 1] - (l - k + 1) << endl;
        }
    }
    return 0;
} 