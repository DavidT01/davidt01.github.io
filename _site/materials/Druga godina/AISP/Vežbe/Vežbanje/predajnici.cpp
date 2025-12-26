// https://arena.petlja.org/competition/asp-rokovi-1#tab_133918

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

    int n; cin >> n;
    vector<int64_t> lokacije(n);
    for(int i = 0; i < n; i++)
        cin >> lokacije[i];
    int64_t d; cin >> d;

    sort(begin(lokacije), end(lokacije));

    int j = 0;
    int64_t maxRazdaljina = -1;
    for(int i = 0; i < n; i++) {
        while(j < i && lokacije[i] - lokacije[j] > d)
            j++;
        maxRazdaljina = max(maxRazdaljina, lokacije[i] - lokacije[j]);
    }

    cout << maxRazdaljina << endl;

    return 0;
}
