#include <iostream>
#include <vector>

using namespace std;

// Graf ima n čvorova i m1 usmerenih grana. U njega je dodato m2 neusmerenih grana.
// Odrediti usmerenja grana tako da graf ostane acikličan.

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

// da bi graf ostao acikličan, grane treba da budu usmerene prema topološkom sortiranju
// graf sa n čvorova i m1 usmerenom granom topološki sortiramo
// u vektoru index na poziciji i čuvamo koji je originalni čvor po tom redu u topološkom sortiranju
// npr. ako je čvor 0 bio 7. po topološkom redosledu, biće index[7] = 0
// nakon toga učitavamo preostalih m2 neusmerenih grana
// ako je index čvora a manji od indeksa čvora b neusmerene grane a - b to znači da treba da je usmerimo od a ka b,
// tj. ispisujemo a -> b, inače ako je indeks od b manji granu usmeravamo ka a, tj. ispisujemo b -> a
int main() {
	int n, m1, m2;
	cin >> n >> m1 >> m2;
	vector<vector<int>> graf(n);
	while(m1--) {
		int a, b;
		cin >> a >> b;
		graf[a].push_back(b);
	}
	vector<int> top = topolosko(graf);
	vector<int> index(n);
	for(int i = 0; i < n; i++)
		index[top[i]] = i;
	while(m2--) {
		int a, b;
		cin >> a >> b;
		if(index[a] < index[b])
			cout << a << " -> " << b << endl;
		else
			cout << b << " -> " << a << endl;
	}
	return 0;
}