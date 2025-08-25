#include <iostream>
#include <vector>

using namespace std;

// vektor roditelj nam služi za održavanje drveta, gde svaki čvor ima svog roditelja
// koreni čvorovi pokazuju sami na sebe, jer nemaju roditelja
// vektor rang će održavati rang, tj. visinu podstabla sa korenom u datom čvoru

vector<int> roditelj;
vector<int> rang;

// na početku svaki element se nalazi u jednom čvoru, pa ćemo imati korena onoliko koliko ima elemenata
// postavljamo roditelja svakog elementa na samog sebe, a rang je svima 1

void napravi_dsu(int n) {
	roditelj.resize(n);
	rang.resize(n, 1);
	for(int i = 0; i < n; i++)
		roditelj[i] = i;
}

// operacija find se implementira tako što prolazimo redom kroz roditelje dok ne dođemo do korenog čvora

int predstavnik(int a) {
	while(roditelj[a] != a)
		a = roditelj[a];
	return a;
}

// pronalazimo predstavnike oba podskupa i ako su jednaki tu je kraj, unija je već izvršena
// uzimamo predstavnika sa manjim rangom i njegovog roditelja postavljamo na drugog predstavnika,
// a potom drugom predstavniku rang uvećamo za rang prvog predstavnika

void unija(int a, int b) {
	a = predstavnik(a);
	b = predstavnik(b);
	if(a == b)
		return;
	if(rang[a] < rang[b]) {
		roditelj[a] = b;
		rang[b] += rang[a];
	}
	else {
		roditelj[b] = a;
		rang[a] += rang[b];
	}
}

int main() {
	int n, a, b; cin >> n;
	napravi_dsu(n);
	while(true) {
		string operacija;
		cin >> operacija;
		if(operacija == "unija") {
			cin >> a >> b;
			unija(a, b);
		}
		else if(operacija == "predstavnik") {
			cin >> a;
			cout << predstavnik(a) << endl;
		}
	}
	return 0;
}