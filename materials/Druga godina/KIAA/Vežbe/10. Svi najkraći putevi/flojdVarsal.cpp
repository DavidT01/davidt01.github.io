#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct grana {
	int sused;
	int duzina;
};

// funkcija koja vrši sabiranje ali uzima u obzir da neka od vrednosti može biti +beskonačno i tada vraća +beskonačno
int addinf(int x, int y) {
	if(x == numeric_limits<int>::max() || y == numeric_limits<int>::max())
		return numeric_limits<int>::max();
	return x + y;
}

// pravimo matricu nxn u kojoj ćemo čuvati vrednosti najkraćih puteva i inicijalizujemo sve vrednosti na +beskonačno
// prolazimo kroz sve grane grafa i postavljamo dužine najkraćih puteva za te direktne grane
// takođe, postavimo dužine najkraćih puteva od čvorova do sebe samih na 0
// u trostrukoj petlji posmatramo trojke čvorova k, i, j:
//      dužinu najkraćeg puta od čvora I do čvora J postavljamo na minimum prethodne vrednosti i zbira najkraćeg puta od I do K i od K do J
// vraćamo matricu D
vector<vector<int>> floyd_warshall(vector<vector<grana>>& graf) {
	int n = graf.size();
	vector<vector<int>> D(n, vector<int>(n, numeric_limits<int>::max()));
	for(int i = 0; i < n; i++)
		for(auto g : graf[i])
			D[i][g.sused] = g.duzina;
	for(int i = 0; i < n; i++)
		D[i][i] = 0;
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				D[i][j] = min(D[i][j], addinf(D[i][k], D[k][j]));
	return D;
}

// Flojd-Varšalov algoritam nam vraća matricu nxn u kojoj se na poziciji (i, j) nalazi najkraći put od čvora i do čvora j
// ako postoji, ili +beskonačno ako ne postoji put
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<grana>> graf(n);
	for(int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
	}
	vector<vector<int>> D = floyd_warshall(graf);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << D[i][j] << ' ';
		cout << endl;
	}
}