#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

// grana sada pored suseda sadrži i dužinu (težinu)
struct grana {
	int sused;
	int duzina;
};

// pravimo vektor u kome ćemo čuvati dužine najkraćih puteva
// dužine najkraćeg puta od čvora u do čvora u je 0, a za sve ostale postavljamo max vrednost iz limits biblioteke
// pravimo skup parova [udaljenost, cvor] gde ćemo čuvati trenutno najmanje udaljenosti do čvorova
// u skup ubacujemo čvor u i udaljenost 0, tj. par [0, u]
// dok god imamo vrednosti u skupu:
//      uzimamo čvor v sa početka skupa i brišemo ga iz skupa
//      prolazimo kroz njegove susede g, tj. kroz grane
//      proveravamo da li za nekog od njegovih suseda možemo da skratimo put
//      ako je dužina puta do čvora v + dužina grane od v do suseda g manja od trenutnog najkraćeg puta do čvora g:
//          iz skupa brišemo postojeći par [udaljenost, cvor] za g
//          postavljamo najkraći put na dužinu puta do čvora v + dužina grane od v do g
//          u skup dodajemo novu vrednost [udaljenost, cvor]
// na kraju vraćamo vektor koji sadrži dužine najkraćih puteva
vector<int> dijkstra(int u, vector<vector<grana>>& graf) {
	vector<int> d(graf.size(), numeric_limits<int>::max());
	d[u] = 0;
	set<pair<int, int>> red;
	red.insert({0, u});
	while(!red.empty()) {
		int v = red.begin()->second;
		red.erase(red.begin());
		for(grana g : graf[v]) {
			if(d[v] + g.duzina < d[g.sused]) {
				red.erase({d[g.sused], g.sused});
				d[g.sused] = d[v] + g.duzina;
				red.insert({d[g.sused], g.sused});
			}
		}
	}
	return d;
}

// pretpostavlja se da su dužine grana pozitivne i potrebno je pronaći dužine najkraćih puteva od čvora 0 do svih ostalih
// dijkstrin algoritam će nam vratiti vektor u kome će se nalaziti tražene vrednosti
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<grana>> graf(n);
	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		graf[a].push_back({b, c});
		graf[b].push_back({a, c});
	}
	vector<int> d = dijkstra(0, graf);
	for(auto x : d)
		cout << x << ' ';
	cout << endl;
	return 0;
}