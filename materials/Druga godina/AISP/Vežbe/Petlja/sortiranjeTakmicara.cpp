#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_132338

//Koristimo našu funkciju koja poredi takmicare rastuće po poenima, a opadajuće po imenima ako je broj poena isti
//Sortiramo niz pomoću napisane funkcije i ispišemo takmičare redom
//Složenost - O(n + nlogn + n) = O(nlogn)

struct Takmicar
{
    string ime;
    int poeni;
};

bool uporedi(const Takmicar& a, const Takmicar& b)
{
    if (a.poeni > b.poeni)
        return true;
    if (a.poeni < b.poeni)
        return false;
    return a.ime <= b.ime;
}

int main()
{
    long n;
    cin >> n;
    Takmicar takmicari[n];
    for (int i = 0; i < n; i++)
        cin >> takmicari[i].ime >> takmicari[i].poeni;
    sort(takmicari, takmicari + n, uporedi);
    for (int i = 0; i < n; i++)
        cout << takmicari[i].ime << " " << takmicari[i].poeni << endl;
    return 0;
}