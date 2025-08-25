#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//Odrediti da li se u datom nizu dužine n nalazi segment čiji je zbir jednak z
//Pr: n = 8, niz = 7 3 -5 8 -2 -1 6 4, z = 9
//rešenje: da

//Zbir segmenta [i, j] možemo predstaviti kao razliku prefiksnih zbirova Z(j+1) - Z(i)
//Sada je samo potrebno pronaći segment za koji važi Z(j+1) - Z(i) = z
//Umesto niza, za čuvanje prefiksnh zbirova koristićemo neuređeni skup koji nam daje
//efikasne metode za umetanje i pretragu elemenata i time smanjujemo složenost
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int z;
    cin >> z;
    bool postojiSegment = false;
    unordered_set<int> Zi;
    Zi.insert(0);
    int pom = 0;
    for (int i = 0; i < n; i++)
    {
        pom += a[i];
        if (Zi.find(pom - z) == Zi.end()) //Metod find vraća pokazivač na kraj skupa ako je pronađen traženi element
        {
            postojiSegment = true;
            break;
        }
        Zi.insert(pom);
    }
    cout << (postojiSegment ? "da" : "ne") << endl;
    return 0;
}