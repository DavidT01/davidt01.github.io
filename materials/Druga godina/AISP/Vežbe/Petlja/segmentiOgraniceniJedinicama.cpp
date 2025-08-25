#include <iostream>
#include <string>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/broj_podstringova_koji_pocinju_i_zavrsavaju_sa_1

//Ako je k broj jedinica u stringu, onda je broj segmenata koji počinju i završavaju sa 1 jednak k * (k - 1) / 2
//Složenost - O(len(niska))

int main()
{
	string niska;
	cin >> niska;
	int i = 0, k = 0;
	while(niska[i])
		if(niska[i++] == '1')
			k++;
	int rez = k * (k - 1) / 2;
	cout << rez << endl;
	return 0;
}
