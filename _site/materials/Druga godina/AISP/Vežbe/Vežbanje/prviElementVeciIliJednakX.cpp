#include <iostream>
#include <vector>

using namespace std;

//U sortiranom nizu pronaći prvi element veći ili jednak zadatom broju x.

//Primenimo algoritam binarne pretrage i nađemo traženi element.
//Drugi način - korišćenje ugrađene funkcije lower_bound(array.begin(), array.end(), x)
//Složenost - O(n + nlogn) = O(nlogn)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int x;
    cin >> x;
    int l = 0, d = n - 1;
    while (l <= d)
    {
        int s = l + (d - l) / 2;
        if (a[s] < x)
            l = s + 1;
        else
            d = s - 1;
    }
    cout << a[l] << endl;
    return 0;
}