#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Odrediti udaljenost svih čvorova od čvora 0.

// umesto vektora za obiđene čvorove, možemo vektor izmeniti da računa udaljenost od čvorova
// na početku udaljenosti inicijalizujemo na -1, osim udaljenosti čvora do samog sebe koju postavljamo na 0 i čvor stavljamo u red
// dok je red neprazan uzimamo čvor iz reda i prolazimo kroz njegove susede
// ako je sused neposećen (udaljenost je -1) dodajemo ga u red i njegovu udaljenost postavljamo na udaljenost čvora koji smo skinuli sa reda + 1,
// jer je čvor t od čvora v udaljen x grana, a onda do čvora u dolazimo preko čvora t što je x + 1 grana

vector<int> bfs(int v, vector<vector<int>>& graf) {
	vector<int> udaljenost(graf.size(), -1);
	queue<int> q;
	q.push(v);
	udaljenost[v] = 0;
	while(!q.empty()) {
		int t = q.front(); q.pop();
		for(int u : graf[t])
			if(udaljenost[u] == -1) {
				q.push(u);
				udaljenost[u] = udaljenost[t] + 1;
			}
	}
	return udaljenost;
}

// pokrećemo BFS koji će vratiti vektor u kome će biti udaljenosti do čvorova

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
	vector<int> udaljenost(n);
    udaljenost = bfs(0, graf);
	return 0;
}