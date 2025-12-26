#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/k_razlika_max_min1

//Sortiramo figurice po jačini i primenimo tehniku dva pokazivača
//Trenutni broj igrača će biti jednak j - i + 1, pa dokle god je razlika jačina trenutnih igrača 
//veća od granice povećavamo levi pokazivač, dok je desni fiksiran
//Kada razlika postane manja ili jednaka od granice, računamo je u posebnoj promenljivoj
//Maksimalni broj igrača i minimalnu razliku za taj broj igrača ažuriramo ako smo postigli veći broj igrača
//od dosadašnjeg ili ako je on isti ali se smanjila minimalna razlika
//Složenost - O(nlogn)

int main()
{
    int n;
    cin >> n;
    vector<int> figurice(n);
    for (int i = 0; i < n; i++)
        cin >> figurice[i];
    sort(begin(figurice), end(figurice)); //O(nlogn)
    uint64_t granica;
    cin >> granica;
    int i = 0;
    uint64_t maxBrIgraca = 0, minRazlika = 0;
    for (int j = 0; j < n; j++) //O(n)
    {
        while ((j - i + 1) * (figurice[j] - figurice[i]) > granica)
            i++;
        uint64_t razlika = (j - i + 1) * (figurice[j] - figurice[i]);
        if (j - i + 1 > maxBrIgraca || (j - i + 1 == maxBrIgraca && razlika < minRazlika))
        {
            maxBrIgraca = j - i + 1;
            minRazlika = razlika;
        }
    }
    cout << maxBrIgraca << ' ' << minRazlika << endl;
    return 0;
}