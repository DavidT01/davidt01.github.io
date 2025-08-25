// https://petlja.org/biblioteka/r/Zbirka2/broj_deljivih_u_intervalu

#include <iostream>

using namespace std;

int main() {
    int a, b, k;
    cin >> a >> b >> k;

    // [a, b] = [0, b] - [0, a - 1], [0, b] = b/k + 1

    int deljiviDoB = b / k + 1;
    int deljiviDoA = (a - 1) / k + 1;
    if(a > 0)
        cout << deljiviDoB - deljiviDoA << endl;
    else
        cout << deljiviDoB << endl;
    return 0;
}