#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/maksimalni_zbir_segmenta

//Odsecamo sve segmente nakon onog kada zbir prvi put postane negativan
//Istovremeno u svakoj iteraciji ažuriramo maksimum
//Sledeći segment kreće od pozicije gde smo stali sa prethodnom proverom(i = j)
//Složenost - O(n + n) = O(n), iako imamo dve ugnježdene petlje

int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int maks = 0;
	for (int i = 0; i < n; i++)
	{
		int zbir = 0;
		int j;
		for (j = i; j < n; j++)
		{
			zbir += a[j];
			if (zbir < 0)
				break;
			if (zbir > maks)
				maks = zbir;
		}
		i = j;
	}
	cout << maks << endl;
	return 0;
}