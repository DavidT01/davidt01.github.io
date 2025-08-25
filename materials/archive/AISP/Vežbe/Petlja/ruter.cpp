#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/ruter

//Dužinu kabla za trenutnu zgradu računamo kao dužinu kablova za prethodnu zgradu plus dužinu kablova levo minus dužinu kablova desno
//Proveravamo da li je dužina manja od trenutnog minimuma i ažuriramo minimum dok ne prođemo sve zgrade
//Složenost - O(n + n) = O(n)

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    uint64_t duzina = 0, levo = 0, desno = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        duzina += a[i] * i;
        desno += a[i];
    }
    uint64_t min = duzina;
    for (int i = 1; i < n; i++) {
        levo += a[i - 1];
        desno -= a[i - 1];
        duzina += levo - desno;
        if (duzina < min)
            min = duzina;
    }
    cout << min << endl;
    return 0;
}