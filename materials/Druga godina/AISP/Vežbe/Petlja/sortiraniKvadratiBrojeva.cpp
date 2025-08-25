#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/sortirani_kvadrati_brojeva

//Pronađemo poziciju prvo nenegativnog broja - p, a zatim primenimo tehniku dva pokazivača
//na niz koji počinje sa pozicije p i niz koji počinje sa pozicije p - 1, pri čemu posebno
//obradimo slučaj kada su svi brojevi niza negativni(p = 0 i a[0] < 0)
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int p = 0;
    for (int i = 0; i < n; i++)
        if (a[i] >= 0)
            {
                p = i;
                break;
            }
    vector<uint64_t> b(n);
    int s = p - 1, k = 0;
    if (p == 0 && a[0] < 0)
    {
        p = n;
        s = n - 1;
    }
    while (s >= 0 && p < n)
    {
        if (abs(a[p]) <= abs(a[s]))
        {
            b[k] = ((uint64_t)a[p]) * ((uint64_t)a[p]);
            p++;
            k++;
        }
        else
        {
            b[k] = ((uint64_t)a[s]) * ((uint64_t)a[s]);
            s--;
            k++;
        }
    }
    while (s >= 0)
    {
        b[k] = ((uint64_t)a[s]) * ((uint64_t)a[s]);
        s--;
        k++;
    }
    while (p < n)
    {
        b[k] = ((uint64_t)a[p]) * ((uint64_t)a[p]);
        p++;
        k++;
    }
    for (int i = 0; i < n; i++)
        cout << b[i] << ' ';
    cout << endl;
    return 0;
}