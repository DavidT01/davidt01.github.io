#include <iostream>
#include <set>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/three_sum

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    set<int> brojevi;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (brojevi.find(- v[i] - v[j]) != end(brojevi))
                k++;
        brojevi.insert(v[i]);
    }
    cout << k << endl;
    return 0;
}