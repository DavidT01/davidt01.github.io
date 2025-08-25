#include <iostream>
#include <set>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/najveci_duplikat1

int main()
{
    int n, x;
    cin >> n;
    set<int> brojevi;
    int najveci = 0;
    while (n--)
    {
        cin >> x;
        if (brojevi.find(x) != end(brojevi) && x > najveci)
            najveci = x;
        brojevi.insert(x);
    }
    if (najveci > 0)
        cout << najveci << endl;
    else
        cout << "nema" << endl;
    return 0;
}