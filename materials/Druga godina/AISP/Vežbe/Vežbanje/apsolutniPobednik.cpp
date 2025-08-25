#include <iostream>
#include <vector>

using namespace std;

//Ako je dat niz glasova za različite kandidate na nekim izborima, odrediti da li
//među njima postoji neki kandidat koji je apsolutni pobednik, 
//tj. koji je osvojio strogo više glasova od svih drugih kandidata zajedno.

//Primetimo da ako sortiramo glasove, u sredini niza će se uvek nalaziti glas za osobu koja je apsolutni pobednik
//To će nam dati nlogn složenost zbor sortiranja, ali možemo dobiti i bolju složenost
// 
//Da bismo pronašli osobu sa najviše glasova koristimo Bojer-Murov algoritam:
// 1. Uklanjamo jedan po jedan par različitih glasova, sve dok postoje bar 2 različita glasa
// 2. Ako ostane prazan skup, polazni skup nema apsolutnog pobednika
// 3. Ako ostane skup koji sadrži glasove samo za jednu osobu, za nju direktno proveravamo da li je apsolutni pobednik
// 
//Da bismo efikasno našli parove različitih glasova, podelićemo originalni skup glasova na dva disjunktna
//U prvom skupu će se nalaziti parovi različitih glasova, a u drugom glasovi koji su isti tj nemaju više kako da se upare
//Konstrukcija ova dva skupa:
// 1.Ako je drugi skup neprazan i ako je novi glas jednak glasovima u njemu, onda ga dodajemo u taj skup
// 2.Inače, jedan glas uparujemo sa novim skupom i dodajemo ih u prvi skup
//Na kraju, ako je drugi skup neprazan to znači da se u njemu nalaze glasovi za jedinog kandidata za apsolutnog pobednika
//pa direktno proveravamo da li on to jeste, a ako je drugi skup prazan apsolutno pobednik ne postoji
// 
//Finalna verzija algoritma:
//Prolazimo kroz niz glasova i održavamo dve promenljive - tekući kandidat za apsolutnog pobedniika i njegov broj glasova do sada
// 1. Ako je broj glasova za kandidata jednak nuli ili je trenutni glas njegov glas, onda je on idalje kandidat i uvećavamo broj glasova
// 2. U suprotnom smanjimo broj glasova za kandidata
//Na kraju, ako je broj glasova pozitivan proveravamo da li je taj kandidat stvarno apsolutni pobednik, a inače apsolutnog pobegnika nema
//Kandidat je apsolutni pobednik ako je njegov broj glasova veći od polovine broja glasova
//Složenost - O(n + n + n) = O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> g(n);
    for (int i = 0; i < n; i++)
        cin >> g[i];
    int kandidat, broj = 0;
    for (int i = 0; i < n; i++)
        if (broj == 0 || g[i] == kandidat)
        {
            kandidat = g[i];
            broj++;
        }
        else
            broj--;
    if (broj > 0 && count(begin(g), end(g), kandidat) > n / 2)
        cout << kandidat << endl;
    else
        cout << "Nema apsolutnog pobednika!" << endl;
    return 0;
}