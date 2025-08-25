#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/trobojka

//Invarijanta petlje: manji od a    - [0, i)
//                    između a i b  - [i, j)
//                    neobrađeni    - [j, k)
//                    veći od b     - [k, n)
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> niz(n);
    for (int i = 0; i < n; i++)
        cin >> niz[i];
    int a, b;
    cin >> a >> b;
    int i = 0, j = 0, k = n;
    while (j < k)
    {
        if (niz[j] < a) //Ako je element iz prve grupe menjamo njega i prvi sledeći neobrađeni element, uvećavamo brojače
            swap(niz[i++], niz[j++]);
        else if (niz[j] <= b) //Ako je element iz druge grupe on je već na mestu, samo povećamo brojač za neobrađene elemente
            j++;
        else //Ako je element iz treće grupe menjamo ga sa poslednjim neobrađenim elementom(pozicija k - 1), istovremeno smanjimo brojač
            swap(niz[j], niz[--k]);
    }
    for (int i = 0; i < n; i++)
        cout << niz[i] << " ";
    cout << "\n";
    return 0;
}
