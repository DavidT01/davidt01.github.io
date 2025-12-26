// https://petlja.org/biblioteka/r/Zbirka2/ne_sadrze_cifru_3

#include <iostream>

using namespace std;

int f(string n) {
    int brCifara = n.size();
    if(brCifara == 0)
        return 1;
    int c = n[0] - '0';
    string devetke(brCifara - 1, '9'), ostatak = n.substr(1);
    if(c < 3)
        return c * f(devetke) + f(ostatak);
    if(c == 3)
        return c * f(devetke);
    return (c - 1) * f(devetke) + f(ostatak);
}

int main() {
    string n; cin >> n;
    cout << f(n) << endl;
    return 0;
}