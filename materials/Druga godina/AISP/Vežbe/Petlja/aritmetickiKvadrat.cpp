#include <iostream>

using namespace std;

int main()
{
    uint64_t n, i;
    cin >> n >> i;
    uint64_t NI = (n * i) % 1000000000;
    uint64_t suma = ((n * (n - 1)) / 2) % 1000000000;
    uint64_t zbirVrste = (n * NI) % 1000000000 + suma;
    uint64_t zbirKolone = NI + (n * suma) % 1000000000;
    cout << zbirVrste % 1000000000 << endl << zbirKolone % 1000000000 << endl;
    return 0;
}