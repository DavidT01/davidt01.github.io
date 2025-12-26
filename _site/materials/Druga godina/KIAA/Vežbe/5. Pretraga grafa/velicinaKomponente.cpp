#include <iostream>
#include <vector>

using namespace std;

// Odrediti broj čvorova komponente povezanosti kojoj pripada čvor 0.

// pri ulasku u čvor označimo da je obiđen i inicijalizujemo broj čvorova koje iz njega obilazimo na 0
// prolazimo kroz njegove susedne čvorove i pokrećemo DFS iz onih koji nisu obiđeni
// rezultat koji vrate te DFS pretrage dodamo na broj čvorova
// na kraju vraćamo broj čvorova uvećan za 1 kako bismo uračunali i trenutni čvor

int dfs(int v, vector<bool>& obidjen, vector<vector<int>>& graf) {
	obidjen[v] = true;
	int brojCvorova = 0;
	for(int u : graf[v])
		if(!obidjen[u])
			brojCvorova += dfs(u, obidjen, graf);
	return brojCvorova + 1;
}

// da bismo odredili broj čvorova u komponenti pokrenemo DFS iz traženog čvora i izmenimo algoritam

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
	vector<bool> obidjen(n);
	cout << dfs(0, obidjen, graf) << endl;
	return 0;
}