// https://petlja.org/biblioteka/r/Zbirka2/bratska_podela

#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

double svePodele(int i, vector<double>& v, double zbirKraja, double zbir1, double zbir2) {
    if(i == v.size())
        return abs(zbir1 - zbir2);

    if(zbir1 + zbirKraja < zbir2)
        return zbir2 - (zbir1 + zbirKraja);
    
    if(zbir2 + zbirKraja < zbir1)
        return zbir1 - (zbir2 + zbirKraja);

    double rezL = svePodele(i + 1, v, zbirKraja - v[i], zbir1 + v[i], zbir2);
    double rezD = svePodele(i + 1, v, zbirKraja - v[i], zbir1, zbir2 + v[i]);
    return min(rezL, rezD);
}

int main() {
    int n; cin >> n;
    vector<double> v(n);
    double zbirKraja = 0;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        zbirKraja += v[i];
    }
    cout << fixed << setprecision(2) << svePodele(0, v, zbirKraja, 0, 0) << endl;
    return 0;
}