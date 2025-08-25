#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<vector<int>> niz(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            niz[i][j] = i * n + j;
    int suma = -niz[0][0] - niz[0][n - 1] - niz[n - 1][0] - niz[n - 1][n - 1];
    for(int i = 0; i < n; i++)
        suma += (niz[0][i] + niz[n - 1][i] + niz[i][0] + niz[i][n - 1]);
    cout << suma << endl;
    return 0;
}