#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/maksimalni_zbir_segmenta1

//m će biti maksimum "vrste", a maks globalni maksimum
//Maksimum računamo kao maksimum dosadašnjeg maksimuma na koji dodajemo tekući član i nule - zbir praznog segmenta
//Nakon toga odmah ažuriramo globalni maksimum
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    int m = 0;
    int maks = m;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        m = max(m + x, 0);
        maks = max(maks, m);
    }
    cout << maks << endl;
    return 0;
}