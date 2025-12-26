#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/prvi_paran

//Invarijanta petlje: deljivi sa k      - [0, i)
//                    neobrađeni        - [i, j)
//                    nisu deljivi sa k - [j, n)
//Koristimo algoritam binarne pretrage jer znamo da su elementi uređeni na osnovu deljivosti sa k
//Složenost jedne iteracije while petlje - O(logn)

int main()
{
    int n;
    cin >> n;
    vector<uint64_t> niz(n);
    for (int i = 0; i < n; i++)
        cin >> niz[i];
    uint64_t k;
    vector<int> rez;
    while (scanf("%ull", &k) != EOF) //Za svaku učitanu vrednost k
    {
        int i = 0, j = n - 1;
        while (i <= j)
        {
            int s = i + (j - i) / 2;
            if (niz[s] % k == 0)
                i = s + 1;
            else
                j = s - 1;
        }
        rez.push_back(j + 1);
    }
    int q = rez.size();
    for (int i = 0; i < q; i++)
        cout << rez[i] << endl;
    return 0;
}
