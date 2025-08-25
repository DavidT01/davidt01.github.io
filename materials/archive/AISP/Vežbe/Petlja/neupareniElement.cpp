#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_132066

//Sortiramo niz da bi isti brojevi bili jedan do drugog
//Gledamo brojeve kao parove pa krećemo od pozicije 1 i brojač svaki put uvećavamo za 2
//Kada su neka dva broja u paru različita ispisujemo onaj na manjoj poziciji(i - 1)
//Na kraju obrađujemo slučaj kada se traženi broj nalazi na poslednjoj poziciji niza
//Složenost - O(nlogn + n) = O(nlogn)

int main()
{
    int n;
    cin >> n;
    int *a = (int*) malloc(n * sizeof(int));
    if (a == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    for (int i = 1; i < n - 1; i += 2)
    {
        if (a[i] != a[i - 1])
        {
            cout << a[i - 1] << endl;
            break;
        }
    }
    if (a[n - 1] != a[n - 2])
        cout << a[n - 1] << endl;
    return 0;
}