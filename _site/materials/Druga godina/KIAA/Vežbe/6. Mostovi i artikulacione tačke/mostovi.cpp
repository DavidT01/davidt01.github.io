#include <iostream>
#include <vector>

using namespace std;

// kada stignemo u novi čvor povećamo promenljivu koja čuva trenutnu dolaznu numeraciju i zapisujemo tu numeraciju u vektoru
// na mestu trenutnog čvora, a low link vrednost takođe inicijalizujemo na u.Pre
// prolazimo kroz susede čvora u:
//      ako im je dolazna numeracija 0 to znači da nisu obiđeni pa se radi o grani DFS drveta:
//          pokrećemo DFS pretragu iz njih (roditelj im je trenutni čvor u) koja nam vraća low link vrednost čvora v
//          ako je ta low link vrednost čvora v veća od dolazne numeracije čvora u ispisujemo granu (u, v) jer je most
//          ažuriramo vrednost low link vrednosti čvora u na minimum prethodne vrednosti i low link čvora v
//      ako je čvor već obiđen, a pritom nije roditelj čvora u to znači da se radi o povratnoj grani:
//          ažuriramo vrednost low link vrednosti čvora u na minimum prethodne vrednosti i dolazne numeracije čvora v
// na kraju vraćamo low link vrednost čvora u
int dfs(int u, int p, int& t, vector<int>& num, vector<vector<int>>& graf) {
	int low = num[u] = ++t;
	for(int v : graf[u])
		if(num[v] == 0) {
			int v_low = dfs(v, u, t, num, graf);
			if(v_low > num[u])
				cout << u << ' ' << v << endl;
			low = min(low, v_low);
		}
		else if(v != p)
			low = min(low, num[v]);
	return low;
}

// grana (u, v) će biti most ako važi da je L(v) > u.Pre, gde je L(v) low link vrednost čvora, a u.Pre dolazna numeracija pri DFS pretrazi
// promenljiva t će održavati redosled čvorova pri DFS pretrazi (pa prosleđujemo po referenci), a vektor num će čuvati dolaznu numeraciju
// prvi argument predstavlja trenutni čvor, a drugi njegov roditelj, roditelj čvora iz kog pokrećemo DFS na početku je on sam

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