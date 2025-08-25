#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Dat je niz od n brojeva. Ispisati redom od najmanjeg ka najvećem sve njihove proste činioce.

// uzimamo m kao najveći element niza
// algoritmom Eratostenovog sita računamo najveći prost delilac svih brojeva od 1 do m:
//      prolazimo kroz brojeve p od 2 do m i ako je najveći prost delilac 0, to znači da broj još nije obiđen i da je prost
//      u tom slučaju prolazimo kroz njegove umnoške (p, 2p, 3p) koji su manji ili jednaki m i postavljamo im najveći delilac na p
// pravimo vektor f gde ćemo čuvati sve delioce
// prolazimo kroz elemente a početnog niza i sve dok su oni različiti od 1:
//      u vektor delilaca f dodajemo najveći prost delilac tog elementa a
//      element ažuriramo na a = a / d[a] da bismo dodali i preostale delioce ako ih ima
// na kraju sortiramo vektor delilaca i ispišemo ga
int main() {
	int n;
	cin >> n;
	vector<int> x(n);
	for(int i = 0; i < n; i++)
		cin >> x[i];

	int m = *max_element(begin(x), end(x));
	vector<int> d(m + 1);
	for(int p = 2; p <= m; p++)
		if(d[p] == 0)
			for(int i = p; i <= m; i += p)
				d[i] = p;

	vector<int> f;
	for(int a : x)
		while(a != 1) {
			f.push_back(d[a]);
			a /= d[a];
		}

	sort(begin(f), end(f));
	for(int a : f)
		cout << a << ' ';
	cout << endl;
	return 0;
}