#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/sve_sortirane_particije

void particije_v1(int n, int maxSabirak, vector<int>& particija)
{
    if (n == 0)
    {
        for (int x : particija)
            cout << x << ' ';
        cout << endl;
        return;
    }
    for (int sabirak = 1; sabirak <= min(n, maxSabirak); sabirak++)
    {
        particija.push_back(sabirak);
        particije_v1(n - sabirak, sabirak, particija);
        particija.pop_back();
    }
}

void particije_v2(int n, int maxSabirak, vector<int> particija)
{
    if (n == 0)
    {
        for (int x : particija)
            cout << x << ' ';
        cout << endl;
        return;
    }
    if (maxSabirak > 1)
        particije_v2(n, maxSabirak - 1, particija);
    if (maxSabirak <= n)
    {
        particija.push_back(maxSabirak);
        particije_v2(n - maxSabirak, maxSabirak, particija);
        particija.pop_back();
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> particija;
    particije_v1(n, n, particija);
    //particije_v2(n, n, particija);
    return 0;
}