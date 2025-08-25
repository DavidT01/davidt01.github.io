#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Date su redom cene akcija tokom n dana. Na koliko načina se može ostvariti pozitivna zarada,
//ako se akcija kupi jednog dana i proda nekog narednog dana?

int mergeSort(int l, int d, vector<int> v, vector<int> tmp)
{
    if (d - l <= 1)
        return 0;
    int s = (l + d) / 2;
    int resLevo = mergeSort(l, s, v, tmp);
    int resDesno = mergeSort(s, d, v, tmp);
    int resUnakrsno = 0;
    int j = l;
    for (int i = s; i < d; i++)
    {
        while (j < s && v[i] >= v[j])
            j++;
        resUnakrsno += j - l;
    }
    merge(begin(v) + l, begin(v) + s, begin(v) + s, begin(v) + d, begin(tmp));
    copy(begin(tmp), begin(tmp) + (d - l), begin(v) + l);
    return resLevo + resDesno + resUnakrsno;
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n), tmp(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    cout << mergeSort(0, n, v, tmp) << endl;
    return 0;
}