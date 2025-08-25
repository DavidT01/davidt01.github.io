#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int k, n; cin >> k >> n;
    vector<int> kolekcije(n);
    for(int i = 0; i < n; i++) {
        cin >> kolekcije[i];
        if(k % kolekcije[i] == 0)
            kolekcije[i] = 1;
        else
            kolekcije[i] = 0;
    }
    vector<int> prefSum(n + 1);
    for(int i = 1; i <= n; i++)
        prefSum[i] = prefSum[i - 1] + kolekcije[i - 1];
    int m; cin >> m;
    while(m--) {
        int a, b; cin >> a >> b;
        cout << prefSum[b + 1] - prefSum[a] << endl;
    }
    return 0;
}