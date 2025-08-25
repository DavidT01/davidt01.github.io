#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/najmanji_nezbir

//Pomoću prvih k elemenata niza možemo dobiti sve brojeve iz intervala [0, a0 + ... + a(k-1)]
//Na zbir dodajemo elemente niza sve dok sledeći element ne postane za 1 veći od zbira prethodnih elemenata tj. ne pripada intervalu
//Najmanji broj koji ne možemo zapisati je onda upravo zbir + 1
//Složenost - O(n + n) = O(n)

int main()
{
	int n;
	cin >> n;
	vector<int> niz(n);
	for(int i = 0; i < n; i++)
		cin >> niz[i];
	int zbir = 0;
	for(int i = 0; i < n; i++)
	{
		if(niz[i] > zbir + 1)
			break;
		zbir += niz[i];
	}
	cout << zbir + 1 << endl;
	return 0;
}
