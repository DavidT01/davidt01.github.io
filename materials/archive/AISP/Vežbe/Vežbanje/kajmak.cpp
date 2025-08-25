// https://arena.petlja.org/competition/asp-rokovi-1#tab_133748

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {

    int n, t; cin >> n >> t;
    vector<int> cene(n);
    for(int i = 0; i < n; i++)
        cin >> cene[i];

    vector<int> ps(n + 1);
    partial_sum(begin(cene), end(cene), begin(ps) + 1);

    int j = 0, maxKolicina = -1;
    for(int i = 1; i < n; i++) {
        while(j < i && ps[i + 1] - ps[j] >= t)
            j++;
        if(ps[i + 1] - ps[j] < t && ps[i + 1] - ps[j] > maxKolicina)
            maxKolicina = ps[i + 1] - ps[j];
        
    }

    cout << maxKolicina << endl;

    return 0;
}