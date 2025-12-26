#include <iostream>
#include <vector>

using namespace std;

// Dato je n računara. Omogućiti operacije spajanja računara, kao i pronalaženje računara sa najmanjim ID-em u mreži.

vector<int> roditelj;
vector<int> rang;

// u vektoru najmanji na poziciji i čuvamo informaciju koji element je najmanji u mreži u kojoj se nalazi čvor i

vector<int> najmanji;

// prilikom pravljenja DSU najmanji čvor je sam taj čvor jer je jedini

void napravi_dsu(int n) {
	roditelj.resize(n);
	rang.resize(n, 1);
	najmanji.resize(n);
	for(int i = 0; i < n; i++) {
		roditelj[i] = i;
		najmanji[i] = i;
	}
}

int predstavnik(int a) {
	while(roditelj[a] != a)
		a = roditelj[a];
	return a;
}

// prilikom spajanja čvoru koji će biti roditeljski (tj. onaj koji je imao veći rang) postavljamo najmanji element
// na minimum najmanjeg elementa oba podskupa koji se spajaju

void unija(int a, int b) {
	a = predstavnik(a);
	b = predstavnik(b);
	if(a == b)
		return;
	if(rang[a] < rang[b]) {
		roditelj[a] = b;
		rang[b] += rang[a];
		najmanji[b] = min(najmanji[a], najmanji[b]);
	}
	else {
		roditelj[b] = a;
		rang[a] += rang[b];
		najmanji[a] = min(najmanji[a], najmanji[b]);
	}
}

// ako se traži najmanji ispisujemo vrednost najmanjeg za predstavnika traženog čvora

int main() {
	int n, m, a, b;
	cin >> n >> m;
	napravi_dsu(n);
	while(m--) {
		string upit;
		cin >> upit;
		if(upit == "povezi") {
			cin >> a >> b;
			unija(a, b);
		}
		else if(upit == "najmanji") {
			cin >> a;
			cout << najmanji[predstavnik(a)] << endl;
		}
	}
	return 0;
}