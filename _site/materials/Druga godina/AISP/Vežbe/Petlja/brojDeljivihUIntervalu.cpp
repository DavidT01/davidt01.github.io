#include <iostream>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_133979

//Broj deljivih u intervalu [a, b] računamo kao razliku deljivih u intervalima [0, b] i [0, a - 1]
//Koristimo sledeće: broj elemenata iz [0, x] deljivih sa k jednak je x / k + 1
//Posebno obrađujemo slučaj kada je a = 0
//Složenost - O(1)

int main()
{
    uint64_t a, b, k;
    cin >> a >> b >> k;
    uint64_t br;
    if (a > 0)
        br = b / k + 1 - ((a - 1) / k + 1);
    else
        br = b / k + 1;
    cout << br << endl;
    return 0;
}