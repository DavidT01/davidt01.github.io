#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/bratska_podela

double podele(int i, vector<double>& v, double zbir, double zbir1, double zbir2)
{
    if (i == v.size())
        return abs(zbir1 - zbir2);
    if (zbir1 + zbir < zbir2)
        return zbir2 - zbir1 - zbir;
    if (zbir2 + zbir < zbir1)
        return zbir1 - zbir2 - zbir;
    double resL = podele(i + 1, v, zbir - v[i], zbir1 + v[i], zbir2);
    double resD = podele(i + 1, v, zbir - v[i], zbir1, zbir2 + v[i]);
    return min(resL, resD);
}

int main()
{
    int n;
    cin >> n;
    vector<double> v(n);
    double zbir = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        zbir += v[i];
    }
    cout << fixed << setprecision(2) << podele(0, v, zbir, 0, 0) << endl;
    return 0;
}