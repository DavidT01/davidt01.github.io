#include <iostream>
#include <set>

using namespace std;

//Napisati funkcije dodaj, obrisi i najblizi pomoću skupa.

void dodaj(int x, set<int> s)
{
    s.insert(x);
}

void obrisi(int x, set<int> s)
{
    s.erase(x);
}

int najblizi(int x, set<int> s)
{
    auto it = s.lower_bound(x);
    if (it == end(s))
        return *(--it);
    if (it == begin(s))
        return *it;
    int a = *it;
    int b = *(--it);
    if (abs(a - x) <= abs(b - x))
        return a;
    return b;
}

int main()
{
    int n;
    cin >> n;
    set<int> s;
    while (n--)
    {
        string op;
        cin >> op;
        int x;
        cin >> x;
        if (op == "dodaj")
            dodaj(x, s);
        else if (op == "obrisi")
            obrisi(x, s);
        else if (op == "najblizi")
            cout << "Najblizi je: " << najblizi(x, s) << endl;
    }
    return 0;
}