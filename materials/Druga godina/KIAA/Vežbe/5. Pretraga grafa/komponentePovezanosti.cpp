#include <iostream>
#include <vector>

using namespace std;

// Odrediti broj komponenti povezanosti grafa.

void dfs(int v, vector<bool>& obidjen, vector<vector<int>>& graf) {
	obidjen[v] = true;
	for(int u : graf[v])
		if(!obidjen[u])
			dfs(u, obidjen, graf);
}

// broj komponenti možemo odrediti tako što redom prođemo kroz sve čvorove grafa
// i pokrenemo DFS pretragu svaki put kada trenutni čvor nije obiđen
// graf će imati onoliko komponenti povezanosti koliko puta je DFS pokrenuta pri tom prolasku kroz čvorove

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
	int brojKomponenti = 0;
	vector<bool> obidjen(n);
	for(int v = 0; v < n; v++)
		if(!obidjen[v]) {
			dfs(v, obidjen, graf);
			brojKomponenti++;
		}
	cout << brojKomponenti << endl;
	return 0;
}