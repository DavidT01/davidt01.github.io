#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka3/prost_broj

//Proveravamo da li je broj deljiv brojevima iz intervala [2, n / 2]
//Složenost - O(sqrt(n))

int main()
{
    uint64_t n;
    cin >> n;
    if (n == 1)
    {
        cout << "NE" << endl;
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            cout << "NE" << endl;
            return 0;
        }
    }
    cout << "DA" << endl;
    return 0;
}