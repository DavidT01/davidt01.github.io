// Koliko segmenata niza daje traženi zbir?

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int mergeSort(int l, int d, int t, vector<int>& v, vector<int>& tmp) {
    if(d - l <= 1)
        return 0;

    int s = (l + d) / 2;
    int brL = mergeSort(l, s, t, v, tmp);
    int brD = mergeSort(s, d, t, v, tmp);

    int brUnakrsno = 0, j = l;
    for(int i = s; i < d; i++) {
        while(j < s && v[i] - v[j] > t)
            j++;
        brUnakrsno += s - j;
    }

    merge(begin(v) + l, begin(v) + s, begin(v) + s, begin(v) + d, begin(tmp));

    copy(begin(tmp), begin(tmp) + d - l, begin(v) + l);

    return brL + brD + brUnakrsno;
}

int main() {
    int t, n; cin >> t >> n;
    vector<int>v(n + 1), tmp(n + 1);
    for(int i = 0; i < n; i++)
        cin >> v[i + 1];
    partial_sum(begin(v), end(v), begin(v));
    cout << mergeSort(0, n + 1, t, v, tmp) << endl;
    return 0;
}