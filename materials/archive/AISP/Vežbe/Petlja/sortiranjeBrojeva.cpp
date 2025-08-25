#include <iostream>
#include <algorithm>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_132337

//Sortiramo niz pomoću ugrađene funkcije sort iz biblioteke algorithm
//Složenost - O(n + nlogn + n) = O(nlogn)

int main()
{
    int n;
    cin >> n;
    int* niz = (int*) malloc(n * sizeof(int));
    if (niz == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++)
        cin >> niz[i];
    sort(niz, niz + n);
    for (int i = 0; i < n; i++)
        cout <<  niz[i] << endl;
    return 0;
}