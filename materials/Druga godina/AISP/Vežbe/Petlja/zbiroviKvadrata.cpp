#include <iostream>
#include <queue>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/zbirovi_kvadrata

int suma(pair<int, int> p)
{
    return p.first * p.first + p.second * p.second;
}

struct comparator
{
    bool operator()(pair<int, int> x, pair<int, int> y)
    {
        if (suma(y) < suma(x))
            return true;
        if (suma(y) > suma(x))
            return false;
        return y.first < x.first;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparator> parovi;
    for (int i = 0; i <= n; i++)
        parovi.push({ i, i });
    while (k--)
    {
        pair<int, int> par = parovi.top();
        parovi.pop();
        if (par.second < n)
            parovi.push({ par.first, par.second + 1 });
    }
    pair<int, int> par = parovi.top();
    cout << par.first << ' ' << par.second << endl;
    return 0;
}