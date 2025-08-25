// https://petlja.org/biblioteka/r/Zbirka2/sortiranje_takmicara

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Takmicar {
    string ime;
    int bodovi;
    bool operator<(Takmicar t) {
        if(bodovi > t.bodovi)
            return true;
        if(t.bodovi > bodovi)
            return false;
        return ime < t.ime;
    }
};

// true - t1 treba ispred t2
bool poredi(Takmicar t1, Takmicar t2) {
    if(t1.bodovi > t2.bodovi)
        return true;
    if(t2.bodovi > t1.bodovi)
        return false;
    return t1.ime < t2.ime;
}

int main() {
    int n; cin >> n;
    vector<Takmicar> takmicari(n);
    for(int i = 0; i < n; i++)
        cin >> takmicari[i].ime >> takmicari[i].bodovi;

    // pisanje funkcije za poređenje
    sort(begin(takmicari), end(takmicari), poredi);

    // ili lambda funkcija
    sort(begin(takmicari), end(takmicari),
        [](Takmicar t1, Takmicar t2) {
            if(t1.bodovi > t2.bodovi)
                return true;
            if(t2.bodovi > t1.bodovi)
                return false;
            return t1.ime < t2.ime;
        });

    // ili predefinisanje operatora u okviru strukture
    sort(begin(takmicari), end(takmicari));

    for(int i = 0; i < n; i++)
        cout << takmicari[i].ime << ' ' << takmicari[i].bodovi << endl;
    return 0;
}