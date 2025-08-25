#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//https://arena.petlja.org/sr-Latn-RS/competition/asp2021-domaci-2#tab_132157

//Sortiramo nizove koji sadrže cene i primenimo tehniku dva pokazivača
//Povećavamo brojač niza koji sadrži manju cenu, ako je to moguće
//Složenost - O(n)

int main()
{
    int m;
    cin >> m;
    vector <int> mOdela(m);
    for (int i = 0; i < m; i++)
        cin >> mOdela[i];
    int z;
    cin >> z;
    vector <int> zOdela(z);
    for (int i = 0; i < z; i++)
        cin >> zOdela[i];
    sort(mOdela.begin(), mOdela.end());
    sort(zOdela.begin(), zOdela.end());
    int minRaz = abs(mOdela[0] - zOdela[0]);
    int i = 0, j = 0;
    while (1)
    {
        if (abs(mOdela[i] - zOdela[j]) < minRaz)
            minRaz = abs(mOdela[i] - zOdela[j]);
        if (mOdela[i] <= zOdela[j])
            if (i < m - 1)
                i++;
            else
                break;
        else
            if (j < z - 1)
                j++;
            else
                break;
    }
    cout << minRaz << endl;
    return 0;
}