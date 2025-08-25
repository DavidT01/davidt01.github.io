// https://petlja.org/biblioteka/r/Zbirka2/three_sum

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];

    set<int> brojevi;
    int brTrojki = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++)
            if(brojevi.find(-v[i] - v[j]) != end(brojevi))
                brTrojki++;
        brojevi.insert(v[i]);
        }
    cout << brTrojki << endl;
    return 0;
}