#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/ne_sadrze_cifru_3

//f(cn) - c je prva cifra broja cn
// 1) c < 3 => f(cn) = c * f(9...9) + f(n)
// 2) c = 3 => f(cn) = c * f(9...9)
// 3) c > 3 => f(cn) = (c-1) * f(9...9) + f(n)

int f_rekurzivno(string n)
{
    int brCif = n.size();
    if (brCif == 0)
        return 1;
    int c = n[0] - '0';
    string devetke(brCif - 1, '9');
    string ostatak = n.substr(1);
    if (c < 3)
        return c * f_rekurzivno(devetke) + f_rekurzivno(ostatak);
    else if (c == 3)
        return c * f_rekurzivno(devetke);
    else
        return (c - 1) * f_rekurzivno(devetke) + f_rekurzivno(ostatak);
}

int f_iterativno(int n)
{
    int resenje = 1;
    int devetke = 1;
    while (n > 0)
    {
        int c = n % 10;
        if (c < 3)
            resenje = c * devetke + resenje;
        else if (c == 3)
            resenje = c * devetke;
        else
            resenje = (c - 1) * devetke + resenje;
        devetke *= 9;
        n /= 10;
    }
    return resenje;
}

int main()
{
    int n;
    cin >> n;
    cout << f_iterativno(n) << endl;
    return 0;
}