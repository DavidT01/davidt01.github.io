#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/maksimalni_zbir_segmenta2

//Pomoću prefiksni zbirova dolazimo do formula za izračunavanje traženog zbira
//z - trenutni prefiksni zbir, minimum - minimum dosadašnjih prefiksnih zbirova, 
//maksimum - maksimum razlike trenutnog prefiksnog zbira i trenutnog minimuma, i prethodnog maksimuma
//Složenost - O(n)

int main()
{
    int n;
    cin >> n;
    int x, z = 0, minimum = 0, maksimum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        minimum = min(minimum, z);
        z += x;
        maksimum = max(maksimum, z - minimum);
    }
    cout << maksimum << endl;
    return 0;
}