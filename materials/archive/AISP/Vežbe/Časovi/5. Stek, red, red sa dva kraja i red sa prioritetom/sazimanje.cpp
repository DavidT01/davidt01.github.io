// https://petlja.org/biblioteka/r/Zbirka2/sazimanje_uzastopnih

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int k, n, x; cin >> k >> n;
    vector<pair<int, int>> s;
    while(n--) {
        cin >> x;
        if(!s.empty() && s.back().first != x && s.back().second >= k)
            s.pop_back();
        if(!s.empty() && s.back().first == x)
            s.back().second++;
        else
            s.push_back({x, 1});
    }

    if(!s.empty() && s.back().second >= k)
        s.pop_back();

    for(int i = 0; i < s.size(); i++)
        while(s[i].second--)
            cout << s[i].first << ' ';
    cout << endl;
    return 0;
}