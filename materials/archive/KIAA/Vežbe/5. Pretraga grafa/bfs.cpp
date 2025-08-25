#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// koristimo vektor da označimo obiđene čvorove, kao i red da bismo stavljali i skidali čvorove
// dodajemo čvor u red i označavamo da je obiđen
// dok je red neprazan skidamo čvor sa vrha i ispisujemo ga
// prolazimo kroz susede čvora i one neobiđene dodajemo na red i označavamo ih kao obiđene

void bfs(int v, vector<vector<int>>& graf) {
	vector<bool> obidjen(graf.size());
	queue<int> q;
	q.push(v);
	obidjen[v] = true;
	while(!q.empty()) {
		int t = q.front(); q.pop();
		cout << t << endl;
		for(int u : graf[t])
			if(!obidjen[u]) {
				q.push(u);
				obidjen[u] = true;
			}
	}
}

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
	bfs(0, graf);
	return 0;
}