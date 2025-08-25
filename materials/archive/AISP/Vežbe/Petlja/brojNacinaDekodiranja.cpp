#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/broj_nacina_dekodiranja

vector<uint64_t> memo;

uint64_t brDekodiranja(string s, int n)
{
    if (memo[n] != -1)
        return memo[n];
    if (n <= 1)
        return memo[n] = 1;
    int b1 = s[n - 1] - '0';
    int b2 = (s[n - 2] - '0') * 10 + s[n - 1] - '0';
    uint64_t br = 0;
    if (b1 != 0)
        br += brDekodiranja(s, n - 1);
    if (b2 >= 10 && b2 <= 26)
        br += brDekodiranja(s, n - 2);
    return memo[n] = br;
}

int main()
{
    string s;
    cin >> s;
    memo = vector<uint64_t>(s.size() + 1, -1);
    cout << brDekodiranja(s, s.size()) << endl;
    return 0;
}