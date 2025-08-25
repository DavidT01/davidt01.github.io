#include <iostream>
#include <vector>

using namespace std;

// Odrediti da li je graf bipartitan.

// kada uđemo u čvor, dodeljujemo mu prosleđenu broju
// prolazimo kroz njegove susede koji nisu obojeni (boja im je 0)
//      pokrenemo DFS iz njih i pritom im dodeljujemo boju 3 - boja čvora koji trenutno posmatramo (jer 1 + 2 = 3)
//      ako neka od pokrenutih BFS pretraga iz suseda vrati false, to znači da nije moguće obojiti ih i vraćamo false
// ako boja nije 0, tj. sused je već obiđen, proverimo da li se boje trenutnog čvora i suseda poklapaju i ako da vraćamo false
// ako na kraju nijedna pretraga nije vratila false, uspešno smo obojili graf (ili bar taj deo grafa) pa vraćamo true

bool dfs(int v, int boja, vector<int>& boje, vector<vector<int>>& graf) {
	boje[v] = boja;
	for(int u : graf[v])
		if(boje[u] == 0) {
			if(!dfs(u, 3 - boja, boje, graf))
				return false;
		}
		else if(boje[u] == boje[v])
			return false;
	return true;
}

// graf je bipartitan ako mu se čvorovi mogu podeliti na dva disjunktna skupa, tako da sve grane grafa povezuju
// čvor iz jednog skupa sa čvorom iz drugog skupa
// graf je bipartitan ako čvorove možemo obojiti pomoću dve boje, tako da nijedna dva susedna čvora nisu obojena istom bojom
// možemo koristiti DFS pretragu gde umesto informacije da li je graf obiđen čuvamo njegovu boju
// čvor sa bojom 0 nije obiđen, čvor sa bojom 1 je plav, čvor sa bojom 2 je crven
// pokrećemo BFS iz čvora 0 i njemu dodelimo npr. boju 1 (ili 2, svejedno je)

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graf(n);
	while(m--) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}
	vector<int> boje(n);
	dfs(0, 1, boje, graf);
	return 0;
}