// https://petlja.org/biblioteka/r/Zbirka2/faktorijeli_od_1_do_n

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    uint64_t fakt = 1;
    for(int i = 1; i <= n; i++)
        cout << (fakt *= i) << endl;
    return 0;
}