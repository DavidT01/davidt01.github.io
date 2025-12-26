#include <iostream>
#include <vector>

using namespace std;

// Odrediti minimalnu vrednost m, tako da je broj n * m potpun kvadrat.

// m inicijalizujemo na 1
// prolazimo redom kroz brojeve p od 2 do sqrt(n):
//		delimo n trenutnim brojem p sve dok je n deljiv njime
//		ako smo ga podelili neparan broj puta množimo m sa p
// na kraju pomnožimo m sa n i vratimo ga
int main() {
	int n;
	cin >> n;
	int m = 1;
	for(int p = 2; p * p <= n; p++) {
		int st = 0;
		while(n % p == 0) {
			n /= p;
			st++;
		}
		if(st % 2 == 1)
			m *= p;
	}
	m *= n;
	cout << m << endl;
	return 0;
}