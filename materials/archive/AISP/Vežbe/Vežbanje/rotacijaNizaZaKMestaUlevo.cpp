#include <iostream>
#include <vector>

using namespace std;

//Definisati funkciju koja bez korišćenja pomoćnog niza, vrši rotaciju
//niza celih brojeva za k mesto ulevo

//Umesto rotiranja jednog po jednog elementa niza, možemo samo izvršiti razmenu blokova elemenata
//Sa Nl i Nd označićemo brojeve elemenata u svakom od dva bloka koja razmenjujemo
//Tada će blod L sadržati elemente na pozicijama (0, Nl), a D na (Nl, Nd)
//Imamo tri slučaja koja razlikujemo na osnovu broja elemenata u blokovima:
// 1. Nl < Nd => delimo D na D1 (Nl, Nd - Nl) i D2 (Nd, Nl)
//               menjamo blokove L (0, Nl) i D2 (Nd, Nl)
//               menjamo blokove D2 (0, Nl) i D1 (Nl, Nd - Nl)
// 2. Nl > Nd => delimo L na L1 (0, Nl - Nd) i L2 (Nl - Nd, Nd)
//               menjamo blokove L2 (Nl - Nd, Nd) i D (Nl, Nd)
//               menjamo blokove L1 (0, Nl - Nd) i D (Nl - Nd, Nd)
// 3. Nl = Nd => menjamo blokove L (0, Nl) i D (Nl, Nd)
//Poslednji slučaj možemo pridružiti nekom od prva dva, i posebno napraviti izlaz iz rekurzije kada su Nl ili Nd nula
//Složenost - O(n) jer svaki element jednom razmenom dolazi na svoje mesto i više se me dira

void razmeni(vector<int>& a, int p1, int p2, int n) //Razmenjuje n elemenata dva bloka koja počinju na pozicijama p1 i p2
{
    for (int i = 0; i < n; i++)
        swap(a[p1 + i], a[p2 + i]);
}

void razmeniBlokoveRekurzivno(vector<int>& a, int nl, int nd)
{
    if (nl == 0 || nd == 0)
        return;
    if (nl < nd)
    {
        razmeni(a, 0, nd, nl);
        razmeniBlokoveRekurzivno(a, nl, nd - nl);
    }
    else
    {
        razmeni(a, nl - nd, nl, nd);
        razmeniBlokoveRekurzivno(a, nl - nd, nd);
    }
}

void razmeniBlokoveIterativno(vector<int>& a, int nl, int nd)
{
    while (nl > 0 && nd > 0)
    {
        if (nl < nd)
        {
            razmeni(a, 0, nd, nl);
            nd -= nl;
        }
        else
        {
            razmeni(a, nl - nd, nl, nd);
            nl -= nd;
        }
    }
}

void rotirajZaKMestaUlevo(vector<int>& a, int k, int n)
{
    k %= n;
    razmeniBlokoveRekurzivno(a, k, n - k);
    //razmeniBlokoveIterativno(a, k, n - k);
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int k;
    cin >> k;
    rotirajZaKMestaUlevo(a, k, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}