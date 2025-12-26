// https://petlja.org/biblioteka/r/Zbirka2/max_zbir_puta_kroz_matricu

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int duzina(vector<vector<int>>& matrica, int n, int m) {
    if(memo[n][m] != -1)
        return memo[n][m];

    if(n == 0 || m == 0)
        return memo[n][m] = 0;

    return memo[n][m] = matrica[n - 1][m - 1] + max(duzina(matrica, n - 1, m), duzina(matrica, n, m - 1));
}

int main() {
    int n; cin >> n;
    vector<vector<int>> matrica (n, vector<int> (n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrica[i][j];
    memo = vector<vector<int>> (n + 1, vector<int> (n + 1, -1));
    cout << duzina(matrica, n, n) << endl;
    return 0;
}