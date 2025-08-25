// https://petlja.org/biblioteka/r/Zbirka2/grejov_kod

#include <iostream>
#include <vector>

using namespace std;

string rekurzivno(unsigned n, unsigned k) {
    if(n == 0)
        return "";
    if(k < (1u << (n - 1)))
        return "0" + rekurzivno(n - 1, k);
    else
        return "1" + rekurzivno(n - 1, (1u << n) - 1 - k);
}

string iterativno(unsigned n, unsigned k) {
    string zapis = "";
    while(n > 0) {
        if(k < (1u << (n - 1)))
            zapis += "0";
        else {
            zapis += "1";
            k = (1u << n) - 1 - k;
        }
        n--;
    }
    return zapis;
}

int main() {
    unsigned n, k; cin >> n >> k;
    cout << rekurzivno(n, k) << endl;
    cout << iterativno(n, k) << endl;
    return 0;
}