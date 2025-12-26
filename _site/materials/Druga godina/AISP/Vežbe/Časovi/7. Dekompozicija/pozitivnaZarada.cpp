// Date su akcije po danima. Na koliko različitih načina se može
// ostvariti pozitivna zarada?

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mergeSort(int l, int d, vector<int>& v, vector<int>& tmp) {
    if(d - l <= 1)
        return 0;

    int s = (l + d) / 2;
    int brL = mergeSort(l, s, v, tmp);
    int brD = mergeSort(s, d, v, tmp);

    int brUnakrsno = 0, j = l;
    for(int i = s; i < d; i++) {
        while(j < s && v[i] <= v[j])
            j++;
        brUnakrsno += j - l;
    }

    merge(begin(v) + l, begin(v) + s, begin(v) + s, begin(v) + d, begin(tmp));
    copy(begin(tmp), begin(tmp) + d - l, begin(v) + l);

    return brL + brD + brUnakrsno;
}

int main() {
    int n; cin >> n;
    vector<int> v(n), tmp(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    cout << mergeSort(0, n, v, tmp) << endl;
    return 0;
}