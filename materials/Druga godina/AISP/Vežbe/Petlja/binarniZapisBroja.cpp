#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/binarni_zapis

//Računamo cifre binarnog zapisa kao ostatak pri deljenju brojem 2 i čuvamo ih u vektoru
//Ispisujemo ih od kraja vektora kako bismo dobili pravilan raspored
//Složenost - O(logn)

int main()
{
	uint64_t n;
	cin >> n;
	vector<int> bin(32);
	int i = 0;
	while(n)
	{
		bin[i++] = n % 2;
		n /= 2;
	}
	for(i = 31; i >= 0; i--)
		cout << bin[i];
	cout << endl;
	return 0;
}
