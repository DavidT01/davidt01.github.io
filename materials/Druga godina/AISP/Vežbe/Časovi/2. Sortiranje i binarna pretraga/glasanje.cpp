// https://petlja.org/biblioteka/r/Zbirka2/najbrojniji_element

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> glasovi(n);
    for(int i = 0; i < n; i++)
        cin >> glasovi[i];

    sort(begin(glasovi), end(glasovi));

    int duzina = 1, maxDuzina = 1;
    for(int i = 1; i < n; i++)
        if(glasovi[i] != glasovi[i - 1])
            duzina = 1;
        else {
            duzina++;
            if(duzina > maxDuzina)
                maxDuzina = duzina;
        }
    cout << maxDuzina << endl;
    return 0;
}