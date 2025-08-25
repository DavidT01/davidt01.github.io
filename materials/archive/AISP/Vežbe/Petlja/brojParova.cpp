#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int parovi(vector<int>& niz, int l, int d, int x)
{
    if (l >= d)
        return 0;
    int s = l + (d - l) / 2;
    int levo = parovi(niz, l, s, x);
    int desno = parovi(niz, s + 1, d, x);
    int br = 0;
    sort(begin(niz) + l, begin(niz) + s + 1);
    sort(begin(niz) + s + 1, begin(niz) + d + 1);
    int i = l, j = d;
    while (i <= s && j > s)
    {
        if (niz[i] + 3 * niz[j] <= x)
        {
            br += j - s;
            i++;
        }
        else
            j--;
    }
    return br + levo + desno;
}

int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> niz(n);
    for (int i = 0; i < n; i++)
        cin >> niz[i];
    cout << parovi(niz, 0, n - 1, d) << endl;
    return 0;
}