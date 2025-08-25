#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/euklid

//Euklidov algoritam: nzd(a, 0) = a, nzd(a, b) = nzd(b, a % b)
//Složenost - O(log(max(a, b)))

int nzd(int a, int b) 
{
	while (b > 0) 
	{
		int tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

int main() 
{
	int a, b, c;
	cin >> a >> b >> c;
	cout << nzd(nzd(a, b), c) << endl;
	return 0;
}
