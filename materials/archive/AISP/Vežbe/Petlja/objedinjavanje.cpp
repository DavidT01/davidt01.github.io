#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/objedinjavanje

//Alociramo niz dužine m+n i u njega upisujemo jedan po jedan član
//Poredimo trenutne članove u početna dva niza, upisujemo manji i povećavamo pokazivač njegovog niza
//Kada dođemo do kraja bar jednog od dva niza, dodajemo preostale članove onog drugog niza
//Da ne bismo proveravali koji je duži napišemo petlje za oba niza, ali će se svakako izvršavati maksimalno jedna
//Složenost - O(m + n)

int main()
{
    int m;
    cin >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++)
        cin >> a[i];
    int n;
    cin >> n;
    vector<int> b(n);
    for (int i = 0; i < n; i++)
        cin >> b[i];
    vector<int> c(m + n);
    int i = 0, j = 0, k = 0;
    while (i < m && j < n)
        c[k++] = a[i] <= b[j] ? a[i++] : b[j++];
    while (i < m)
        c[k++] = a[i++];
    while (j < n)
        c[k++] = b[j++];
    for (int p = 0; p < m + n; p++)
        cout << c[p] << ' ';
    cout << endl;
    return 0;
}