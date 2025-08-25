#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/minimum_rotiranog_sortiranog_niza

//Možemo zapaziti da je minimum(1) prvi element manji ili jednak od poslednjeg elementa(13)
//Algoritmom binarne pretrage nalazimo prvi element manji ili jednak poslednjem elemntu niza.
//Složenost - O(n + nlogn) = O(nlogn)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int l = 0, d = n - 1;
    while (l <= d)
    {
        int s = l + (d - l) / 2;
        if (a[s] > a[n - 1])
            l = s + 1;
        else
            d = s - 1;
    }
    cout << a[l] << endl;
    return 0;
}