#include <iostream>
#include <vector>

using namespace std;

// u vektoru indeg ćemo čuvati ulazne stepene svih čvorova
// na početku prođemo kroz sve grane u -> v i povećamo ulazni stepen čvora v
// u vektoru q čuvamo sve čvorove koji trenutno imaju ulazni stepen 0
// prolazimo kroz vektor q:
//      uzimamo trenutni čvor u
//      prolazimo kroz njemu susedne čvorove i smanjujemo im ulazni stepen
//      ako nekima od njih stepen postao 0 dodamo ih u vektor q
// na kraju vraćamo vektor q jer su tu čvorovi dodavani redom kako im je ulazni stepen postajao 0, a to odgovara topološkom sortiranju
vector<int> topolosko(vector<vector<int>>& graf) {
	int n = graf.size();
	vector<int> indeg(n);
	for(int u = 0; u < n; u++)
		for(int v : graf[u])
			indeg[v]++;
	vector<int> q;
	for(int u = 0; u < n; u++)
		if(indeg[u] == 0)
			q.push_back(u);
	for(int i = 0; i < q.size(); i++) {
		int u = q[i];
		for(int v : graf[u]) {
			indeg[v]--;
			if(indeg[v] == 0)
				q.push_back(v);
		}
	}
	return q;
}

// ako smo u rezultujućem vektoru dobili manje čvorova od n, u grafu postoji ciklus
// inače, ispisujemo čvorove redom kojim se nalaze u vektoru
int main() {
	int n, m;
	cin >> n >> m;
	vector< vector<int> > graf(n);
	while(m--) {
		int a, b; // usmerena grana a -> b
		cin >> a >> b;
		graf[a].push_back(b);
	}
	vector<int> top = topolosko(graf);
	if(top.size() < n) {
		cout << "ciklus" << endl;
	}
	else {
		for(int u : top)
			cout << u << ' ';
		cout << endl;
	}
}