// Koliki je zbir brojeva u datom redu sledećeg trougla?

//           1
//         2 3 4
//       5 6 7 8 9
// 10 11 12 13 14 15 16
//          ...

#include <iostream>

using namespace std;

int main() {

    int k;
    cin >> k;

    // oduzmemo veći trougao od manjeg
    // krajnji element trougla je k^2
    // 1 + 2 + . . . + n = n(n + 1) / 2

    long long zbir1 = k * k * (k * k + 1) / 2;
    long long zbir2 = (k - 1) * (k - 1) * ((k - 1) * (k - 1) + 1) / 2;
    cout << zbir1 - zbir2 << endl;

    // najbolje rešenje se dobija sređivanjem formule do kraja!
    cout << 2 * k * k * k - 3 * k * k + 3 * k - 1 << endl;
    return 0;
}