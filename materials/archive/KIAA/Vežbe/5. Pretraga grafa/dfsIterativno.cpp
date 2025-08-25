#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// koristimo vektor da pamtimo koje smo čvorove obišli, kao i stek da na njega stavljamo i skidamo čvorove
// na početku stavimo čvor na stek i označimo da je obiđen
// dok je stek neprazan, skidamo čvor sa vrha steka i ispisujemo ga
// redom prolazimo kroz njegove susede i one koji nisu obiđeni dodamo na stek i označimo kao obiđene

void dfs(int v, vector<vector<int>>& graf) {
	vector<bool> obidjen(graf.size());
	stack<int> q;
	q.push(v);
	obidjen[v] = true;
	while(!q.empty()) {
		int t = q.top(); q.pop();
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
	dfs(0, graf);
	return 0;
}