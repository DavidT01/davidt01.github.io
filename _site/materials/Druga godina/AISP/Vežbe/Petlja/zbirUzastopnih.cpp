#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/rastavljanja_na_zbir_uzastopnih

//Predstavimo broj kao zbir uzastopnih: n = A0 + A1 + .... + A(m - 1)
//Iz formule za zbir aritmetičkog niza: n = m * A0 + m * (m / 1) / 2
//Odavde je A0 = (n - m * (m - 2) / 2) / m
//Odavde znamo da ćemo broj n moći zapisati kao zbir m uzastopnih sabiraka počevši od A0 jedino ako je izraz sa desne strane ceo broj
//Složenost - O(n * sqrt(n))

int main()
{
	uint64_t n;
	cin >> n;
	int k = 0;
	for (uint64_t m = 2; m + m * (m - 1) / 2 <= n; m++)
		if ((n - m * (m - 1) / 2) % m == 0)
			k++;
	cout << k << endl;
	return 0;
}