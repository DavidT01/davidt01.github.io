#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/faktorijeli_od_1_do_n

//Pamtimo faktorijel prethodnog broja i preko njega računamo sledeci: fact(n) = fact(n - 1) * n
//Složenost - O(n)

int main()
{
	int n;
	cin >> n;
	if (n > 0)
	{
		uint64_t fact = 1;
		for (int i = 1; i <= n; i++)
		{
			fact *= i;
			cout << fact << endl;
		}
	}
	return 0;
}