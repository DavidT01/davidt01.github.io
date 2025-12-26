// https://petlja.org/biblioteka/r/Zbirka2/najbrojniji_element1

#include <iostream>
#include <map>

using namespace std;

int main() {
    int n; cin >> n;
    map<string, int> mapa;
    string ime;
    while(n--) {
        cin >> ime;
        mapa[ime]++;
    }
    int maxGlasova = 0;
    for(auto p : mapa)
        if(p.second > maxGlasova)
            maxGlasova = p.second;
    cout << maxGlasova << endl;
    return 0;
}