#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/najduzi_zajednicki_podniz_stringa

int main()
{
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] != b[j - 1])
                dp[i][j] = max(dp[i - 1][i], dp[i][j - 1]);
            else
                dp[i][j] = 1 + dp[i - 1][j - 1];
    cout << dp[n][n] << endl;
    return 0;
}