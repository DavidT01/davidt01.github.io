#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// sve je isto kao kod operacija uvećavanja i zbira, samo se koeficijent propagacije ne nadodaje (+=) na već postojeći
// već se upisuje nova vrednost, tako da se segment ne uvećava za neki broj već se taj broj dodeljuje svim članovima segmenta

struct cvor {
	int vrednost = 0;
	int dodela = 0;
};

int velicina(int n) {
	return pow(2, ceil(log2(n)));
}

vector<cvor> napravi_stablo(vector<int>& niz, int n) {
	vector<cvor> stablo(2 * n);
	for(int i = 0; i < niz.size(); i++)
		stablo[n + i].vrednost = niz[i];
	for(int i = n - 1; i > 0; i--)
		stablo[i].vrednost = stablo[2 * i].vrednost + stablo[2 * i + 1].vrednost;
	return stablo;
}

void propagiraj(int i, int tl, int td, vector<cvor>& stablo) {
	stablo[i].vrednost = stablo[i].dodela * (td - tl + 1);
	if(tl < td) {
		stablo[2 * i].dodela = stablo[i].dodela;
		stablo[2 * i + 1].dodela = stablo[i].dodela;
	}
	stablo[i].dodela = 0;
}

void dodeli(int l, int d, int dodela, int idx, int tl, int td, vector<cvor>& stablo) {
	if(stablo[idx].dodela != 0)
		propagiraj(idx, tl, td, stablo);
	if(l > td || d < tl) return;
	if(tl >= l && td <= d) {
		stablo[idx].dodela = dodela;
		propagiraj(idx, tl, td, stablo);
	}
	else {
		int s = (tl + td) / 2;
		dodeli(l, d, dodela, 2 * idx, tl, s, stablo);
		dodeli(l, d, dodela, 2 * idx + 1, s + 1, td, stablo);
		stablo[idx].vrednost = stablo[2 * idx].vrednost + stablo[2 * idx + 1].vrednost;
	}
}

int upit(int l, int d, int idx, int tl, int td, vector<cvor>& stablo) {
	if(stablo[idx].dodela != 0)
		propagiraj(idx, tl, td, stablo);
	if(l > td || d < tl) return 0;
	if(tl >= l && td <= d)
		return stablo[idx].vrednost;
	else {
		int s = (tl + td) / 2;
		int zbirL = upit(l, d, 2 * idx, tl, s, stablo);
		int zbirD = upit(l, d, 2 * idx + 1, s + 1, td, stablo);
		return zbirL + zbirD;
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	int sn = velicina(n);
	vector<cvor> stablo = napravi_stablo(a, sn);
	while(true) {
		string operacija;
		cin >> operacija;
		if(operacija == "dodeli") {
			int l, d, u;
			cin >> l >> d >> u;
			dodeli(l, d, u, 1, 0, sn - 1, stablo);
		}
		else if(operacija == "upit") {
			int l, d;
			cin >> l >> d;
			cout << upit(l, d, 1, 0, sn - 1, stablo) << endl;
		}
	}
	return 0;
}