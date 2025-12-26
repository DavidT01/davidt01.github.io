// https://arena.petlja.org/competition/asp-rokovi-1#tab_133923

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; i++)
        cin >> x[i];
    int d; cin >> d;

    sort(x.begin(), x.end());

    int maks = 0, j = 0;
    for (int i = 0; i < n; i++) {
        while(x[i] - x[j] > 2 * d)
            j++;
        maks = max(maks, i - j + 1);
    }

    cout << maks << endl;

    return 0;
}