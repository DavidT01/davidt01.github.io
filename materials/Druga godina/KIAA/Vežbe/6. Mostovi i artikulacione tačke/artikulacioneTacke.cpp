#include <iostream>
#include <vector>

using namespace std;

// uvećavamo trenutnu dolaznu numeraciju, pamtimo je u nizu za trenutni čvor i na istu vrednost inicijalizujemo low link
// promenljivu ap postavljamo na false i ona označava da li je čvor artikulaciona tačka
// promenljiva count broji broj dece u DFS drvetu za trenutni čvor, inicijalizujemo je na 0
// prolazimo kroz sve susede čvora u:
//      ako je dolazna numeracija 0, čvor nije obiđen i radi se grani DFS drveta:
//          računamo low link čvora v, tj. pokrećemo DFS
//          ako trenutni čvor u nije koren (num[u] > 1) i ako je low link v veći ili jednak dolaznoj numeraciji u, čvor u je artikulaciona tačka
//          low link mu ažuriramo na minimum prethodne vrednosti i low link čvora v
//          povećavamo broj dece u DFS drvetu za 1
//      ako je čvor već obiđen, a pritom nije roditelj čvora u:
//          low link ažuriramo na minimum prethodne vrednosti i dolazne numeracije čvora v
// ispisujemo čvor u ako je artikulaciona tačka, tj. ako ispunjava jedan od dva uslova:
//      koren je DFS drveta (num[u] == 1) i ima više od dva deteta u DFS drvetu (count > 1)
//      zadovoljava uslov za low link koji smo prethodno proveravali (ap == true)
// na kraju vraćamo low link vrednost čvora u
int dfs(int u, int p, int& t, vector<int>& num, vector<vector<int>>& graf) {
	int low = num[u] = ++t;
	bool ap = false;
	int count = 0;
	for(int v : graf[u])
		if(num[v] == 0) {
			int v_low = dfs(v, u, t, num, graf);
			if(num[u] > 1 && v_low >= num[u])
				ap = true;
			low = min(low, v_low);
			count++;
		}
		else if(v != p)
			low = min(low, num[v]);
	if(ap || (num[u] == 1 && count > 1))
		cout << u << ' ';
	return low;
}

// kao i slučaju mostova, pokrećemo DFS i računamo low link vrednosti
// čvor je artikulaciona tačka ako važi jedan od dva uslova:
//      čvor je koren DFS drveta i ima bar dva deteta
//      čvor nije koren DFS drveta i za neko njegovo dete v u DFS drvetu važi L(v) >= u.Pre

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
	int t = 0;
	vector<int> num(n, 0);
	dfs(0, 0, t, num, graf);
	return 0;
}