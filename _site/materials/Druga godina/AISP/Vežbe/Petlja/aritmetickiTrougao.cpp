#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/aritmeticki_trougao1

//Uočimo sume svih trouglova - 1; 1 + 2 + 3 + 4; 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9
//Suma k-tog trougla - 1 + 2 + ... + k^2 = k^2 * (k^2 + 1) / 2
//Suma k-tog reda jednaka je razlici sume k-tog trougla i (k-1)-og trougla
//Nakon sređivanja izraza dobijamo da je suma k-tog reda jednaka 2k^3 - 3k^2 + 3k - 1
//Složenost - O(1)

int main()
{
	uint64_t k;
	cin >> k;
	uint64_t suma = 2 * k * k * k - 3 * k * k + 3 * k - 1;
	cout << suma << endl;
	return 0;
}