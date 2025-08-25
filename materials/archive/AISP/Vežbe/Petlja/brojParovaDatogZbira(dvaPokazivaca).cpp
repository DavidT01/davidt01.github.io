#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/broj_parova_datog_zbira2

//Sortiramo niz i primenimo tehniku dva pokazivača
//Ako je trenutni zbir manji od traženog povečavamo levu granicu, ako je veći smanjujemo desnu,
//a ako smo našli traženi zbir ažuriramo obe granice i povećamo broj traženih parova
//Složenost - O(nlogn)

int main()
{
	int s, n;
	cin >> s >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(begin(a), end(a)); //O(nlogn)
	int brParova = 0;
	int i = 0, j = n - 1;
	while (i < j) //O(n)
	{
		if (a[i] + a[j] < s)
			i++;
		else if (a[i] + a[j] > s)
			j--;
		else
		{
			i++;
			j--;
			brParova++;
		}
	}
	cout << brParova << endl;
	return 0;
}