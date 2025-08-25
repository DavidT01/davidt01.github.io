#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/broj_rastucih_segmenata

//Fiksiramo levi kraj segmenta i nađemo najduži segment koji je strogo rastući(desni kraj će biti j)
//Ako je njegova dužina m = i - j, broj njegovih podsegmenata(koji su takođe rastući) je m * (m - 1) / 2
//Pretragu nastavljamo od pozicije gde smo stali u prethodnoj iteraciji(i = j)
//Složenost - O(n + n) = O(n), iako imamo dve ugnježdene petlje

int main()
{
    int n;
    cin >> n;
    vector<long long int> a(n);
    for (int p = 0; p < n; p++)
        cin >> a[p];
    long long k = 0;
    int i = 0;
    while (i < n)
    {
        int j = i + 1;
        while (j < n && a[j] > a[j - 1])
            j++;
        long long m = j - i;
        k += m * (m - 1) / 2;
        i = j;
    }
    cout << k << endl;
    return 0;
}