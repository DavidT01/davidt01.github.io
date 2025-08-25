#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<int> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];
    vector<int> brSkokova = vector<int>(n, n);
    brSkokova[n - 1] = 0;
    for(int i = n - 2; i >= 0; i--)
        for(int a = niz[i]; a > 0; a--)
            if(i + a < n)
                brSkokova[i] = min(brSkokova[i], brSkokova[i + a] + 1);
    if(brSkokova[0] != n)
        cout << brSkokova[0] << endl;
    else
        cout << -1 << endl;
    return 0;
}