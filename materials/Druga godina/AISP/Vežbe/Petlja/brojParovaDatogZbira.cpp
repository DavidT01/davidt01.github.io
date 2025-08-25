#include <iostream>
#include <set>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/broj_parova_datog_zbira1

int main()
{
    int s, n, x;
    cin >> s >> n;
    set<int> brojevi;
    int k = 0;
    while (n--)
    {
        cin >> x;
        if (brojevi.find(s - x) != end(brojevi))
            k++;
        brojevi.insert(x);
    }
    cout << k << endl;
    return 0;
}