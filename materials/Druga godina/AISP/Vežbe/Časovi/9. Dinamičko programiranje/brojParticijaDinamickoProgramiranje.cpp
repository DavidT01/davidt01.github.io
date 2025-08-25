// https://petlja.org/biblioteka/r/Zbirka2/broj_particija

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<int>> dp = vector<vector<int>> (n + 1, vector<int> (n + 1));
    dp[0] = vector<int>(n + 1, 1);
    for(int i = 1; i <= n; i++)
        for(int maxSabirak = 1; maxSabirak <= n; maxSabirak++) {
            dp[i][maxSabirak] += dp[i][maxSabirak - 1];
            if(maxSabirak <= i)
                dp[i][maxSabirak] += dp[i - maxSabirak][maxSabirak];
        }
    cout << dp[n][n] << endl;
    return 0;
}