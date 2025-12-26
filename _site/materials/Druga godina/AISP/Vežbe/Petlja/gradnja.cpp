#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/gradnja

//Fiksiramo prvu kuću na početak ulice, a zatim postavljamo kuće na lokacije udaljene bar d od poslednje kuće
//dokle god je to moguće. Ako je na kraju broj kuća 0 to znači da smo sve kuće postavili i moguće je postaviti 
//kuće tako da d bude traženo D(g), a inače nije moguće pa funkcija vraća false
//Na kraju ćemo primeniti binarnu pretragu po rešenju i ažurirati konačno rešenje
//Složenost - O(nlogn)

bool ispitajRastojanje(int d, int brKuca, vector<int>& lokacije, int brLokacija) //O(n)
{
    brKuca--;
    int poslednjaLokacija = lokacije[0];
    for(int i = 1; i < brLokacija && brKuca > 0; i++)
        if (lokacije[i] - poslednjaLokacija >= d)
        {
            brKuca--;
            poslednjaLokacija = lokacije[i];
        }
    return brKuca == 0;
}

int main()
{
    int brKuca, brLokacija;
    cin >> brKuca >> brLokacija;
    vector<int> lokacije(brLokacija);
    for (int i = 0; i < brLokacija; i++)
        cin >> lokacije[i];
    sort(begin(lokacije), end(lokacije));
    int l = 1, d = lokacije[brLokacija - 1]; //Najmanje moguće d je 1, a najveće je rastojanje poslednje lokacije od početka ulice
    int resenje = -1;
    while (l <= d) //O(logn)
    {
        int s = l + (d - l) / 2;
        if (ispitajRastojanje(s, brKuca, lokacije, brLokacija))
        {
            resenje = s;
            l = s + 1;
        }
        else
            d = s - 1;
    }
    cout << resenje << endl;
    return 0;
}