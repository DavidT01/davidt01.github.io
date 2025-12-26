#include <iostream>
#include <deque>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/svi_ispred_manji_ili_svi_ispred_veci

int main()
{
    int n;
    cin >> n;
    deque<int> d;
    int x;
    while (n--)
    {
        cin >> x;
        if (d.empty() || x < d.front())
            d.push_front(x);
        else
            d.push_back(x);
    }
    for (int i = 0; i < d.size(); i++)
        cout << d[i] << " ";
    cout << endl;
    return 0;
}