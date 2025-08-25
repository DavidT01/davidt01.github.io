// https://arena.petlja.org/competition/asp-rokovi-1#tab_133920

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<int64_t> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];

    sort(begin(niz), end(niz));
    vector<int64_t> ps(n + 1);
    partial_sum(begin(niz), end(niz), begin(ps) + 1);

    int q; cin >> q;
    while(q--) {
        int64_t x; cin >> x;
        cout << ps[upper_bound(begin(niz), end(niz), x) - begin(niz)] << endl;
    }

    return 0;
}