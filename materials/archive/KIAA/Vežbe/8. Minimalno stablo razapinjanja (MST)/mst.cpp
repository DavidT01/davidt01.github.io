#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

struct grana {
	int sused;
	int tezina;
};

// vektor dodat označava koji su čvorovi dodati u stablo
// vektor stablo sadrži informaciju o roditelju čvora u stablu i dužinu grane do roditelja
// inicijalizujemo na početku svim čvorovima roditelja na -1 a dužinu grane na +beskonačno
// pravimo skup koji sadrži vrednosti (tezina, cvor)
// na početku dodamo čvor 0 i njemu težinu stavimo na 0
// dok skup nije prazan:
//		uzimamo čvor čija je težina najmanja i brišemo ga iz skupa
//		obeležimo da je čvor dodat u stablo
//		prolazimo kroz njegove susede:
//			ako sused nije dodat u stablo težina grane mu je manja od dosadašnje:
//				brišemo par (težina, cvor) iz skupa
//				ažuriramo vrednost
//				ubacimo novu vrednost u skup
// na kraju vratimo stablo
vector<grana> prim(vector<vector<grana>>& graf) {
	vector<bool> dodat(graf.size());
	vector<grana> stablo(graf.size(), {-1, numeric_limits<int>::max()});
	set<pair<int, int>> red;
	red.insert({0, 0});
	while(!red.empty()) {
		int v = red.begin()->second;
		red.erase(red.begin());
		dodat[v] = true;
		for(auto g : graf[v]) {
			if(!dodat[g.sused] && g.tezina < stablo[g.sused].tezina) {
				red.erase({stablo[g.sused].tezina, g.sused});
				stablo[g.sused] = {v, g.tezina};
				red.insert({stablo[g.sused].tezina, g.sused});
			}
		}
	}
	return stablo;
}

// Primov algoritam određuje minimalno razapinjuće stablo
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
	vector<grana> stablo = prim(graf);
	int mst = 0;
	for(grana g : stablo)
		if(g.sused != -1)
			mst += g.tezina;
	cout << mst << endl;
	return 0;
}