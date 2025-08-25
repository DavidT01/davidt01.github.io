#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/segmenti_deljivi_sa_k

//Prvo odredimo ostatke pri deljenju sa k svih prefiksnih zbirova
//Kada oduzmemo ostatke dva segmenta i dobijemo nulu to znači da je taj segment deljiv sa k
//Nulu ćemo dobiti jedino ako su ostaci isti(k - k = 0) što znaci da za ostatak k imamo k * (k - 1) / 2 segmenata koji su deljivi sa k
//Na kraju ćemo sumirati segmente za sve ostatke pri deljenju sa k(od 0 do k - 1)
//Složenost - O(n + k)

int main()
{
    int k, n;
    cin >> k >> n;
    vector<int> brPojavljivanja(k, 0);
    int z = 0;
    brPojavljivanja[0] = 1;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        z = (z + x % k) % k;
        brPojavljivanja[z]++;
    }
    long long brSegmenata = 0;
    for (int i = 0; i < k; i++)
        brSegmenata += brPojavljivanja[i] * (brPojavljivanja[i] - 1) / 2;
    cout << brSegmenata << endl;
    return 0;
}