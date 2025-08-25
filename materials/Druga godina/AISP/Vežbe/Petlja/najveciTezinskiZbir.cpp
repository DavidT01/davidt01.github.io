#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/suma_posle_ciklicnog_pomeranja

//Težinski zbir nakon i pomeranja: Zi = 0*Ai + 1*A(i+1) + ... + (n-2)*A(i-2) + (n-1)*A(i-1)
//                  i+1 pomeranja: Z(i+1) = 0*A(i+1) + 1*A(i+2) + ... + (n-2)*A(i-1) + (n-1)*Ai
//Iz razlike ovih zbirova dobijamo: Z(i+1) = Zi - (A0 + A1 + ... + A(n-1)) + n * Ai
//                                         = Zi - sumaNiza + n * a[i - 1] (petlja ide od 1 pa Ai postaje a[i - 1])
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> niz(n);
    int Zi = 0, sumaNiza = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> niz[i];
        Zi += (i * niz[i]) % 1234567;
        Zi %= 1234567;
        sumaNiza += niz[i];
    }
    int maxSuma = Zi, brojPomeranja = 0;
    for (int i = 1; i < n; i++)
    {
        Zi = (Zi - sumaNiza + n * niz[i - 1]) % 1234567;
        if (Zi > maxSuma)
        {
            maxSuma = Zi;
            brojPomeranja = i;
        }
    }
    cout << brojPomeranja << endl << maxSuma << endl;
    return 0;
}