#include <iostream>
#include <vector>

using namespace std;

int usisaj(vector<vector<int>>& soba, int i, int j, int usisano, int zaUsisavanje, int n, int m) {
    if(soba[i][j] == 2 && usisano == zaUsisavanje - 1)
        return 1;
    if(soba[i][j] == 2)
        return 0;
    int rez = 0, tmp = soba[i][j];
    soba[i][j] = -1;
    if(i + 1 < n && soba[i + 1][j] != -1)
        rez += usisaj(soba, i + 1, j, usisano + 1, zaUsisavanje, n, m);
    if(j + 1 < m && soba[i][j + 1] != -1)
        rez += usisaj(soba, i, j + 1, usisano + 1, zaUsisavanje, n, m);
    if(i - 1 >= 0 && soba[i - 1][j] != -1)
        rez += usisaj(soba, i - 1, j, usisano + 1, zaUsisavanje, n, m);
    if(j - 1 >= 0 && soba[i][j - 1] != -1)
        rez += usisaj(soba, i, j - 1, usisano + 1, zaUsisavanje, n, m);
    soba[i][j] = tmp;
    return rez;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> soba(n, vector<int>(m));
    int Pi, Pj, zaUsisavanje = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            cin >> soba[i][j];
            if(soba[i][j] == 1) {
                Pi = i;
                Pj = j;
            }
            if(soba[i][j] != -1)
                zaUsisavanje++;
        }
    cout << usisaj(soba, Pi, Pj, 0, zaUsisavanje, n, m) << endl;
    return 0;
}