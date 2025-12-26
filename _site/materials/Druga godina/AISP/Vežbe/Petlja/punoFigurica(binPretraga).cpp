#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/k_razlika_max_min

//Pošto smo sortirali niz brojeva to znači da ćemo minimalnu razliku između dva igrača među k igrača dobiti kao
//razliku jačina na pozicijijama (i + k - 1) i (i)
//Na kraju primenimo binarnu pretragu po rešenju i ažuriramo maksimalni broj igrača i minimalnu razliku jačina dva igrača
//za taj broj igrača
//Složenost - O(nlogn)

uint64_t minRazlika(int brIgraca, int brFigurica, vector<uint64_t>& figurice) //O(n)
{
    uint64_t minRaz = numeric_limits<uint64_t>::max();
    for (int i = 0; i + brIgraca - 1 < brFigurica; i++)
        minRaz = min(minRaz, brIgraca * (figurice[i + brIgraca - 1] - figurice[i]));
    return minRaz;
}

int main()
{
    int brFigurica;
    cin >> brFigurica;
    vector<uint64_t> figurice(brFigurica);
    for (int i = 0; i < brFigurica; i++)
        cin >> figurice[i];
    sort(begin(figurice), end(figurice));
    uint64_t granica;
    cin >> granica;
    int l = 1, d = brFigurica;
    uint64_t maxBrIgraca, minRaz;
    while (l <= d) //O(logn)
    {
        int s = l + (d - l) / 2;
        uint64_t razlika = minRazlika(s, brFigurica, figurice);
        if (razlika <= granica)
        {
            maxBrIgraca = s;
            minRaz = razlika;
            l = s + 1;
        }
        else
            d = s - 1;
    }
    cout << maxBrIgraca << ' ' << minRaz << endl;
    return 0;
}