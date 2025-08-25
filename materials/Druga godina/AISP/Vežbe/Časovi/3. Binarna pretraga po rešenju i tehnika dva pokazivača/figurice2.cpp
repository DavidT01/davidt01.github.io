// https://petlja.org/biblioteka/r/Zbirka2/k_razlika_max_min1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int64_t> jacine(n);
    for(int i = 0; i < n; i++)
        cin >> jacine[i];

    int64_t t; cin >> t;

    sort(begin(jacine), end(jacine));

    int64_t j = 0, maxK = 0, razlika = 0;
    for(int64_t i = 0; i < n; i++) {
        while((i - j + 1) * (jacine[i] - jacine[j]) > t)
            j++;
        int64_t tRaz = (i - j + 1) * (jacine[i] - jacine[j]);
        if(i - j + 1 > maxK || (i - j + 1 == maxK && tRaz < razlika)) {
            maxK = i - j + 1;
            razlika = tRaz;
        }
    }
    cout << maxK << ' ' << razlika << endl;
    return 0;
}