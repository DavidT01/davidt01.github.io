#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

//https://arena.petlja.org/sr-Latn-RS/competition/asp2021-domaci-2#tab_134047

//Primenimo binarnu pretragu po rešenju za sve moguće vrednosti dubina
//Prvo ćemo sortirati niz koji sadrži visine
//Funkcija koja proverava da li određena dubina može biti rešenje računa sumu pritisaka na sve segmente
//Pritisak na jedan segment se računa kao razlika posmatrane dubine i visine segmenta
//Kada saberemo pritiske svih segmenata proveravamo da li je ukupan pritisak manji ili jednak onom koji podmornica može da izdrži
//Složenost - O(nlogn)

bool proveriDubinu(vector<unsigned long long>& visine, unsigned long long dubina, unsigned long long p)
{
    unsigned long long suma = 0, i;
    for (i = 0; (visine[i] < dubina) && (i < visine.size()); i++)
    {
        suma += dubina - visine[i];
    }
    if (suma <= p)
        return true;
    return false;
}

int main()
{
    unsigned long long n, p;
    cin >> n >> p;
    vector<unsigned long long> visine(n);
    for (unsigned long long i = 0; i < n; i++)
        cin >> visine[i];
    sort(begin(visine), end(visine));
    unsigned long long l = 0, d = visine[n - 1] + p;
    while (l <= d)
    {
        unsigned long long s = l + (d - l) / 2;
        if (proveriDubinu(visine, s, p))
            l = s + 1;
        else
            d = s - 1;
    }
    cout << d << endl;
    return 0;
}