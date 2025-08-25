//https://arena.petlja.org/competition/asp-rokovi-1#tab_133919

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n; cin >> n;
    vector<int> niz(n);
    for(int i = 0; i < n; i++)
        cin >> niz[i];

    vector<int> tmp = niz;
    sort(begin(tmp), end(tmp));

    for(int i = 0; i < n; i++) {
        auto it = lower_bound(begin(tmp), end(tmp), niz[i]);
        niz[i] = it - begin(tmp);
    }

    for(int i = 0; i < n; i++)
        cout << niz[i] << ' ';
    cout << endl;

    return 0;
}