#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/problemi/Zbirka/broj_formiran_od_datih_cifra_sleva_na_desno

//Formiramo dekadni broj primenom Hornerove sheme
//Složenost - O(1)

int main()
{
	uint64_t broj = 0;
	int cifra, i = 0;
	while(i < 9 && scanf("%d", &cifra) != EOF)
	{	
		broj = broj * 10 + cifra;
		i++;
	}
	cout << broj << endl;
	return 0;
}
