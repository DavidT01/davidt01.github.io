// https://petlja.org/biblioteka/r/Zbirka2/svi_ispred_manji_ili_svi_ispred_veci

#include <iostream>
#include <deque>

using namespace std;

int main() {
    int n, x; cin >> n;
    deque<int> d;
    while(n--) {
        cin >> x;
        if(d.empty() || x < d.front())
            d.push_front(x);
        else
            d.push_back(x);
    }
    for(int i = 0; i < d.size(); i++)
        cout << d[i] << ' ';
    return 0;
}