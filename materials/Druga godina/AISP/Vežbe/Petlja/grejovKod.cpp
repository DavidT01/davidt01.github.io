#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/grejov_kod

//Za k < 2^(n-1) Grejov kod dužine m jednak na poziciji k jednak je Grejovom kodu dužine m-1 na poziciji m - 1 - k
//Za k < 2^(n-1) prva cifra je 0, a inače 1

string grejov_kod_rekurzivno(unsigned n, unsigned k)
{
    if (n == 0)
        return "";
    if (k < (1u << (n - 1)))
        return "0" + grejov_kod_rekurzivno(n - 1, k);
    else
        return "1" + grejov_kod_rekurzivno(n - 1, (1u << n) - 1 - k);
}

string grejov_kod_iterativno(unsigned n, unsigned k)
{
    string zapis = "";
    while (n > 0)
    {
        if (k < (1u << (n - 1)))
            zapis = "0";
        else
        {
            zapis += "1";
            k = (1u << n) - 1 - k;
        }
        n--;
    }
    return zapis;
}

int main()
{
    unsigned n, k;
    cin >> n >> k;
    cout << grejov_kod_iterativno(n, k) << endl;
    return 0;
}