// https://arena.petlja.org/competition/asp-rokovi-1#tab_133925

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int t; cin >> t;

    sort(begin(a), end(a));

    int brojac = 0;
    for(int i = 0; i < n; i++)
        if(binary_search(begin(a), end(a), t ^ a[i]))
            brojac++;

    cout << brojac / 2 << endl;

    return 0;
}