#include <iostream>
#include <vector>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_133977

//ost0 - brojevi deljivi sa 3, ost1 - pri deljenju sa 3 daju ostatak 1, ost2 - pri deljenju sa 3 daju ostatak 2
//Kombinacije dvojki čiji zbir daje broj koji je deljiv sa 3:
//      dva broja deljiva sa 3 - ost0 * (ost0 - 1) / 2
//      jedan broj daje ostatak 1, drugi ostatak 2 - ost1 * ost2
//Kombinacije trojki čiji zbir daje broj koji je deljiv sa 3:
//      tri broja deljiva sa 3 - ost0 * (ost0 - 1) * (ost0 - 2) / 6
//      tri broja koja daju ostatak 1 - ost1 * (ost1 - 1) * (ost1 - 2) / 6
//      tri broja koja daju ostatak 2 - ost2 * (ost2 - 1) * (ost2 - 2) / 6
//      jedan broj deljiv sa 3, drugi daje ostatak 1, treci daje ostatak 2 - ost0 * ost1 * ost2
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    int ost0 = 0, ost1 = 0, ost2 = 0;
    for (int i = 0; i < n; i++) //Računamo koliko brojeva je deljivo sa 3, koliko daje ostatak 1, a koliko ostatak 2
    {
        cin >> a[i];
        if (a[i] % 3 == 0)
            ost0++;
        else if (a[i] % 3 == 1)
            ost1++;
        else
            ost2++;
    }
    //Saberemo sve kombinacije
    cout << (ost0 * (ost0 - 1)) / 2 + ost1 * ost2 + (ost0 * (ost0 - 1) * (ost0 - 2)) / 6 + ost0 * ost1 * ost2 + (ost1 * (ost1 - 1) * (ost1 - 2)) / 6 + (ost2 * (ost2 - 1) * (ost2 - 2)) / 6 << endl;
    return 0;
}