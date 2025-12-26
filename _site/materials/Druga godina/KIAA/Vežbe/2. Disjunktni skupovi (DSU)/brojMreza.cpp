#include <iostream>
#include <vector>

using namespace std;

// Dato je n računara. Računari se spajaju u mreže m puta. Odrediti koliko različitih mreža je ostalo posle m spajanja.

vector<int> roditelj;
vector<int> rang;

void napravi_dsu(int n) {
	roditelj.resize(n);
	rang.resize(n, 1);
	for(int i = 0; i < n; i++)
		roditelj[i] = i;
}

int predstavnik(int a) {
	while(roditelj[a] != a)
		a = roditelj[a];
	return a;
}

// modifikujemo union operaciju tako da vraća true ako su dva računara spojena u mrežu, a false ako nisu
// vraćamo false ako su predstavnici oba računara jednaka, jer su onda računari već bili u mreži
// u suprotnom izvršimo spajanje i vraćamo true

bool unija(int a, int b) {
	a = predstavnik(a);
	b = predstavnik(b);
	if(a == b)
		return false;
	if(rang[a] < rang[b]) {
		roditelj[a] = b;
		rang[b] += rang[a];
	}
	else {
		roditelj[b] = a;
		rang[a] += rang[b];
	}
	return true;
}

// pravimo DSU sa n čvorova, tako da na početku imamo n mreža
// ako smo stvarno spojili dve do tada nepovezane mreže smanjujemo broj mreža za 1

int main() {
	int n, m, a, b;
	cin >> n >> m;
	napravi_dsu(n);
	int brojMreza = n;
	while(m--) {
		cin >> a >> b;
		if(unija(a, b))
			brojMreza--;
	}
    cout << brojMreza << endl;
	return 0;
}