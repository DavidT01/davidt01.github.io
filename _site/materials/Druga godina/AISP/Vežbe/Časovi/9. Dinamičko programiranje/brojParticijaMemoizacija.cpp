// https://petlja.org/biblioteka/r/Zbirka2/broj_particija

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int brParticija(int n, int maxSabirak) {
    if(memo[n][maxSabirak] != -1)
        return memo[n][maxSabirak];

    if(n == 0)
        return memo[n][maxSabirak] = 1;

    int br = 0;

    if(maxSabirak > 1)
        br += brParticija(n, maxSabirak - 1);

    if(maxSabirak <= n)
        br += brParticija(n - maxSabirak, maxSabirak);

    return memo[n][maxSabirak] = br;
}

int main() {
    int n; cin >> n;
    memo = vector<vector<int>> (n + 1, vector<int> (n + 1, -1));
    cout << brParticija(n, n) << endl;
    return 0;
}