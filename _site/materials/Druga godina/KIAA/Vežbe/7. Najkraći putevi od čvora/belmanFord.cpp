#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct grana {
	int sused;
	int duzina;
};

// vektor koji čuva najkraće puteve inicijalizujemo kao i kod Dijkstrinog algoritma, 0 od čvora do samog sebe, a +beskonačno za ostale
// n - 1 puta vršimo relaksacije svih puteva, odnosno n - 1 puta prolazimo kroz svaki čvor v:
//		ako je najkraći put do tog čvora manji od +beskonačno, odnosno ako je već prethodno pronađen prolazimo kroz njegove grane, tj. susedne čvorove:
//			dužinu najkraćeg puta do tih suseda postavljamo na minimum prethodne vrednosti i zbira najkraćeg puta do čvora v i dužine grane od v do posmatranog suseda
// na kraju vraćamo vektor koji čuva dužine najkraćih puteva
vector<int> bellman_ford(int u, vector<vector<grana>>& graf) {
	int n = graf.size();
	vector<int> d(n, numeric_limits<int>::max());
	d[u] = 0;
	for(int i = 0; i < n - 1; i++)
		for(int v = 0; v < n; v++)
			if(d[v] < numeric_limits<int>::max())
				for(grana g : graf[v])
					d[g.sused] = min(d[g.sused], d[v] + g.duzina);
	return d;
}

// kod Belman-Fordovog algoritma dužine grana mogu biti i negativne ali ne sme postojati ciklus negativne dužine
// algoritam vraća vektor gde se nalaze dužine najkraćih puteva od prosleđenog čvora do svih ostalih
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<grana>> graf(n);
	for(int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
	}
	vector<int> D = bellman_ford(0, graf);
	for(int i = 0; i < n; i++)
		cout << D[i] << ' ';
	cout << endl;
}