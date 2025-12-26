#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//https://arena.petlja.org/competition/asp2021-domaci-1#tab_132128

//Računamo kilometražu za pre i posle servisiranja svakog dana
//Za prvi dan će vrednost pre biti kilometraža tog dana(jer se servisira na kraju dana), a vrednost posle zbir svih drugih kilometraža
//Ostale vrednosti za pre i posle računamo po formulama:
//                                         pre[i + 1] = pre[i] + a[i]
//                                         posle[i + 1] = posle[i] - a[i]
//Zatim ažuriramo vrednost trenutne razlike(|pre - posle|) i minimuma
//Na kraju ispisujemo prvi dan čija se razlika poklapa sa minimumom
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    long pre, posle = 0;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++)
        posle += a[i];
    pre = a[0];
    vector<long> razlike(n);
    razlike[0] = abs(pre - posle);
    long Min = razlike[0];
    for (int i = 1; i < n; i++)
    {
        pre += a[i];
        posle -= a[i];
        razlike[i] = abs(pre - posle);
        Min = min(Min, razlike[i]);
    }
    for (int i = 0; i < n; i++)
        if (Min == razlike[i])
        {
            cout << i << endl;
            return 0;
        }
}