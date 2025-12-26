// https://petlja.org/biblioteka/r/Zbirka2/k_razlika_max_min

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int64_t minRazlika(int x, vector<int64_t>& jacine, int n) {
    int64_t minR = numeric_limits<int64_t>::max();
    for(int i = 0; i <= n - x; i++)
        minR = min(minR, x * (jacine[i + x - 1] - jacine[i]));
    return minR;
}

int main() {
    int n; cin >> n;
    vector<int64_t> jacine(n);
    for(int i = 0; i < n; i++)
        cin >> jacine[i];

    sort(begin(jacine), end(jacine));

    int64_t t; cin >> t;
    int l = 2, d = n;
    pair<int, int64_t> rez = {-1, -1};
    while(l <= d) {
        int s = (l + d) / 2;
        int64_t minR = minRazlika(s, jacine, n);
        if(minR <= t) {
            rez = {s, minR};
            l = s + 1;
        }
        else
            d = s - 1;
    }
    cout << rez.first << ' ' << rez.second << endl;
    return 0;
}