#include <iostream>
#include <map>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/najbrojniji_element1

int main()
{
    int n;
    cin >> n;
    map<string, int> glasovi;
    while (n--)
    {
        string ime;
        cin >> ime;
        glasovi[ime]++;
    }
    int maxGlasova = 0;
    for (auto p : glasovi)
        if (p.second > maxGlasova)
            maxGlasova = p.second;
    cout << maxGlasova << endl;
    return 0;
}