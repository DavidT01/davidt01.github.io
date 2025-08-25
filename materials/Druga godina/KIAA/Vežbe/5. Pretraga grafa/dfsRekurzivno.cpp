#include <iostream>
#include <vector>

using namespace std;

// kada uđemo u čvor označimo da je obiđen i ispišemo ga
// prilazimo redom kroz njegove susede i pokrećemo DFS pretragu iz onih koji nisu obiđeni

void dfs(int v, vector<bool>& obidjen, vector<vector<int>>& graf) {
	obidjen[v] = true;
	cout << v << endl;
	for(int u : graf[v])
		if(!obidjen[u])
			dfs(u, obidjen, graf);
}

// koristimo matricu da pamtimo susede svih čvorova, kao i jedan vektor da bismo pamtili koje čvorove smo obišli

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
	dfs(0, obidjen, graf);
	return 0;
}