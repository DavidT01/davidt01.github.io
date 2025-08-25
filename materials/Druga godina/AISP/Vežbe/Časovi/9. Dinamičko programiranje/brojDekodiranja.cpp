// https://petlja.org/biblioteka/r/Zbirka2/broj_nacina_dekodiranja

#include <iostream>
#include <vector>

using namespace std;

vector<uint64_t> memo;

uint64_t dekodiraj(string& s, int n) {
    if(memo[n] != -1)
        return memo[n];

    if(n <= 1)
        return 1;

    int b1 = s[n - 1] - '0';
    int b2 = (s[n - 2] - '0') * 10 + (s[n - 1] - '0');
    uint64_t br = 0;
    if(b1 != 0)
        br += dekodiraj(s, n - 1);
    if(b2 > 9 && b2 < 27)
        br += dekodiraj(s, n - 2);
    return memo[n] = br;
}

int main() {
    string kod; cin >> kod;
    memo = vector<uint64_t> (kod.size() + 1, -1);
    cout << dekodiraj(kod, kod.size()) << endl;
    return 0;
}