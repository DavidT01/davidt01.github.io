// https://petlja.org/biblioteka/r/Zbirka2/zbirovi_kvadrata

#include <iostream>
#include <queue>

using namespace std;

int suma(pair<int, int> a) {
    return a.first * a.first + a.second * a.second;
}

// funkcija vraca true za onaj element koji treba da se izbaci
// npr. manji element, veci element, manji po nekoj vrednosti itd
struct comparator {
    bool operator()(pair<int, int> x, pair<int, int> y) {
        if(suma(y) < suma(x))
            return true;
        if(suma(y) > suma(x))
            return false;
        return y.first < x.first;
    }
};

int main() {
    int n, k; cin >> n >> k;
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparator> q;
    for(int i = 0; i <= n; i++)
        q.push({i, i});
    
    while(k--) {
        pair<int, int> t = q.top();
        q.pop();
        if(t.second < n)
            q.push({t.first, t.second + 1});
    }
    pair<int, int> rez = q.top();
    cout << rez.first << ' ' << rez.second << ' ' << suma(rez) << endl;
    return 0;
}