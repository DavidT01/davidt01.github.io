#include <iostream>
#include <map>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/segment_celih_datog_zbira1

int main()
{
    int z, n, x;
    cin >> z >> n;
    map<int, int> brPrefiksa;
    brPrefiksa[0] = 1;
    int suma = 0, brSegmenata = 0;
    while (n--)
    {
        cin >> x;
        suma += x;
        brSegmenata += brPrefiksa[suma - z];
        brPrefiksa[suma]++;
    }
    cout << brSegmenata << endl;
    return 0;
}