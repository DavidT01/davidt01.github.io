#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>

using namespace std;

int main()
{
    int n, k;
    cin >> k >> n;
    map<string, int> glasovi;
    set<string> glasano;
    string kandidat;
    int proslo = 0;
    while (n--)
    {
        cin >> kandidat;
        glasovi[kandidat]++;
        if (glasovi[kandidat] >= k && glasano.find(kandidat) == glasano.end())
        {
            proslo++;
            glasano.insert(kandidat);
        }
        cout << proslo << endl;
    }
    return 0;
}