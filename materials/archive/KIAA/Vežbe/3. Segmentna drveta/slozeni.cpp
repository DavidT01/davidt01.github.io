#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Za niz od n elemenata i date intervale [l, d] odrediti koliko je elemenata niza složeno.

int velicina(int n) {
	return pow(2, ceil(log2(n)));
}

vector<int> napravi_stablo(vector<int>& niz, int n) {
	vector<int> stablo(2 * n);
	copy(begin(niz), end(niz), begin(stablo) + n);
	for(int k = n - 1; k > 0; k--)
		stablo[k] = stablo[2 * k] + stablo[2 * k + 1];
	return stablo;
}

void postavi(int i, int x, vector<int>& stablo, int n) {
	stablo[i += n] = x;
	for(i /= 2; i > 0; i /= 2)
		stablo[i] = stablo[2 * i] + stablo[2 * i + 1];
}

int upit(int l, int d, vector<int>& stablo, int n) {
	int brSlozenih = 0;
	for(l += n, d += n; l <= d; l /= 2, d /= 2) {
		if(l % 2 == 1) brSlozenih += stablo[l++];
		if(d % 2 == 0) brSlozenih += stablo[d--];
	}
	return brSlozenih;
}

// vraća 1 (true) ako je broj složen, a 0 (false) ako je prost

int slozen(int n) {
	for(int d = 2; d * d <= n; d++)
		if(n % d == 0)
			return 1;
	return 0;
}

// umesto elemenata niza, možemo da čuvamo samo informaciju da li je broj složen ili ne, što radimo pomoću funkcije iznad
// rešenje se onda svodi na prostu implementaciju segmentnog drveta za sabiranje, gde pri unošenju ne unosimo vrednost elementa,
// već da li je složen ili ne

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
		v[i] = slozen(v[i]);
	}
	int sn = velicina(n);
	vector<int> stablo = napravi_stablo(v, sn);
	while(true) {
		string komanda;
		cin >> komanda;
		if(komanda == "postavi") {
			int i, x;
			cin >> i >> x;
			postavi(i, slozen(x), stablo, sn);
		}
		else {
			int l, d;
			cin >> l >> d;
			cout << upit(l, d, stablo, sn) << '\n';
		}
	}
	return 0;
}