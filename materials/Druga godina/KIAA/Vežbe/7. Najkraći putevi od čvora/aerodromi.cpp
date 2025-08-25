#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

// Odrediti najkraći put od čvora A do čvora C, koji ide preko čvora B.

struct grana {
	int sused;
	int duzina;
};

int dijkstra(int u, int k, vector<vector<grana>>& graf) {
	vector<int> d(graf.size(), numeric_limits<int>::max());
	d[u] = 0;
	set< pair<int, int> > red;
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
	return d[k];
}

// pokrećemo Dijkstrin algoritam iz čvora A i iz čvora B
// iz prvog poziva uzimamo dužinu najkraćeg puta do B, a iz drugog dužinu najkraćeg puta do C
// rešenje će biti zbir ovih vrednosti
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
	int a, b, c;
	cin >> a >> b >> c;
	int AB = dijkstra(a, b, graf);
	int BC = dijkstra(b, c, graf);
	cout << AB + BC << endl;
	return 0;
}