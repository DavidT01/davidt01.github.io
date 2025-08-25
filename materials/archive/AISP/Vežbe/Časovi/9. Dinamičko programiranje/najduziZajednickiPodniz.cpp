// https://petlja.org/biblioteka/r/Zbirka2/najduzi_zajednicki_podniz_stringa

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int duzina(string& a, string& b, int n, int m) {
    if(memo[n][m] != -1)
        return memo[n][m];

    if(n <= 0 || m <= 0)
        return memo[n][m] = 0;

    if(a[n - 1] != b[m - 1])
        return memo[n][m] = max(duzina(a, b, n - 1, m), duzina(a, b, n, m - 1));
    else
        return memo[n][m] = 1 + duzina(a, b, n - 1, m - 1);
}

int main() {
    string a, b; cin >> a >> b;
    int N = a.size(), M = b.size();
    vector<vector<int>> dp(N + 1, vector<int> (M + 1));
    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++) {
            if(a[n - 1] != b[m - 1])
                dp[n][m] = max(dp[n - 1][m], dp[n][m - 1]);
            else
                dp[n][m] = 1 + dp[n - 1][m - 1];
        }
    memo = vector<vector<int>> (a.size() + 1, vector<int> (b.size() + 1, -1));
    cout << duzina(a, b, a.size(), b.size()) << endl;
    return 0;
}