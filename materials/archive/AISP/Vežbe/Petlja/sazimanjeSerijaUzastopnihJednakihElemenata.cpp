#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/sazimanje_uzastopnih

int main()
{
    int k, n, x;
    cin >> k >> n;
    vector<int> vrednosti;
    vector <int> duzine;
    while (n--)
    {
        cin >> x;
        if (!vrednosti.empty() && vrednosti.back() != x && duzine.back() >= k)
        {
            vrednosti.pop_back();
            duzine.pop_back();
        }
        if (!vrednosti.empty() && vrednosti.back() == x)
            duzine.back()++;
        else
        {
            vrednosti.push_back(x);
            duzine.push_back(1);
        }
    }
    if (!vrednosti.empty() && duzine.back() >= k)
    {
        vrednosti.pop_back();
        duzine.pop_back();
    }
    for (int i = 0; i < vrednosti.size(); i++)
    {
        while (duzine[i]--)
            cout << vrednosti[i] << ' ';
    }
    cout << endl;
    return 0;
}