#include <iostream>
#include <vector>

using namespace std;

// čuvamo vektor veličine n + 1, gde na poziciji i čuvamo informaciju da li je broj i složen ili ne
// broj 1 označavamo kao složen
// prolazimo redom kroz brojeve od 2 do sqrt(n):
//      ako je trenutni broj d prost prolazimo kroz sve njegove umnoške (d*d, d*d + d, d*d + 2d, ...) koji su manji ili jednaki od n
//      označavamo da su oni složeni
int main() {
	int n;
	cin >> n;
	vector<bool> slozen(n + 1);
	slozen[1] = true;
	for(int d = 2; d * d <= n; d++)
		if(!slozen[d])
			for(int i = d * d; i <= n; i += d)
				slozen[i] = true;

	for(int d = 2; d <= n; d++)
		if(!slozen[d])
			cout << d << ' ';
	cout << endl;
	return 0;
}