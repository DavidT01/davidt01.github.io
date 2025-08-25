#include <iostream>
#include <vector>

using namespace std;

//https://arena.petlja.org/competition/asp2021-domaci-1#tab_132088

//Koristimo algoritam dvobojke jer su poeni takmičara sortirani
//Invarijanta petlje: iznad praga - [0, i)
//                    neobrađeni - [i, j)
//                    ispod praga - [j, n)
//Za svaki od m pragova koristimo gornji algoritam i ispisujemo broj takmičara iznad praga što će na kraju biti vrednost pozicije i
//Složenost - O(n + m * logn)

int main()
{
    long n;
    cin >> n;
    vector<int> takmicari(n);
    for (long i = 0; i < n; i++)
        cin >> takmicari[i];
    int m;
    cin >> m;
    while (m--)
    {
        int prag;
        cin >> prag;
        long i = 0, j = n;
        while (i < j)
        {
            long s = i + (j - i) / 2;
            if (takmicari[s] >= prag)
                i = s + 1;
            else
                j = s;
        }
        cout << i << endl;
    }
    return 0;
}