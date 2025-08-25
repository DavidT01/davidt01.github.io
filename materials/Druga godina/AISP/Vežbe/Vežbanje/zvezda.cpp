#include <iostream>
#include <vector>

using namespace std;

//Napisati program koji na osnovu matrice poznanstava određuje da li postoji i ko je zvezda
//Osoba je zvezda u nekoj grupi ako nju poznaje svaki drugi član te grupe, a ona ne poznaje nikoga

//Iz polaznog skupa eliminišemo jednu po jednu osobu za koju sigurno znamo da nije zvezda
//Kada dođemo do toga da je ostala jedna osoba, tada je ona jedini kandidat da bude zvezda
//Lako možemo pronaći osobe koje nisu zvezda i izbacivati ih:
// 1. Ako A poznaje B, A nije zvezda
// 2. Ako A ne poznaje B, B nije zvezda
//Koristimo tehniku dva pokazivača i u svakom koraku gledamo osobe na poziciji i i j:
// 1. Ako osoba i poznaje osobu j, i ne može biti zvezda, pa uvećavamo pozivač j, a i postavljamo na staru vrednost j
// 2. Ako osoba i ne poznaje osobu j, j ne može biti zvezda, pa uvećavamo pokazivač j
//Na kraju, kada pokazivač j dođe do n, jedini kandidat za zvezdu je osoba na poziciji i, što na kraju proveravamo posebno
//Složenost - O(n^2) - i tehnika dva pokazivača i provera jedinog kandidata za zvezdu su linearne složenosti,
//ali zbog unosa vrednosti u matricu složenost je linearna

bool poznajeNekoga(const vector<vector<bool>>& poznanstva, int i)
{
    int n = poznanstva.size();
    for (int j = 0; j < n; j++)
        if (j != i && poznanstva[i][j])
            return true;
    return false;
}

bool sviJePoznaju(const vector<vector<bool>>& poznanstva, int i)
{
    int n = poznanstva.size();
    for (int j = 0; j < n; j++)
        if (j != i && !poznanstva[j][i])
            return false;
    return true;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<bool>> poznanstva(n, vector<bool>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> poznanstva[i][j];
    int i = 0;
    for (int j = 1; j < n; j++)
        if (poznanstva[i][j])
            i = j;
    if (sviJePoznaju(poznanstva, i) && !poznajeNekoga(poznanstva, i))
        cout << i << endl;
    else
        cout << "Ne postoji zvezda!" << endl;
    return 0;
}