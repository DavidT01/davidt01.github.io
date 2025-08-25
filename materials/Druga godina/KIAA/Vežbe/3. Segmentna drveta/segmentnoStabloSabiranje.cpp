#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// funkcija računa prvi stepen dvojke veći ili jednak n

int velicina(int n) {
	return pow(2, ceil(log2(n)));
}

// veličina stabla se inicijalizuje na 2n (prošireno n)
// kopiramo početni niz na poziciju n u stablu
// sve ostale listove (od n - 1 do 1) računamo kao zbir prethodnih po formuli:
//      drvo[k] = drvo[2k] + drvo[2k + 1]
// na kraju vraćamo napravljeno stablo

vector<int> napravi_stablo(vector<int>& niz, int n) {
	vector<int> stablo(2 * n);
	copy(begin(niz), end(niz), begin(stablo) + n);
	for(int k = n - 1; k > 0; k--)
		stablo[k] = stablo[2 * k] + stablo[2 * k + 1];
	return stablo;
}

// pri ažuriranju elementa na poziciji i, prvo pređemo na vrednost i + n jer se u stablu elementi nalaze pomereni za n mesta
// ažuriramo element na toj poziciji na novu vrednost
// prolazimo redom kroz njegove roditelje (i/2 dok ne dođemo do 1) i ponovo računamo njihovu vrednost kao zbir dece

void postavi(int i, int x, vector<int>& stablo, int n) {
    i += n;
	stablo[i] = x;
	for(i /= 2; i > 0; i /= 2)
		stablo[i] = stablo[2 * i] + stablo[2 * i + 1];
}

// na početku zbir segmenta [l, d] inicijalizujemo na 0
// ažuriramo im vrednosti da bi odgovarale stablu, tj. uvećamo ih za n
// idemo na gore sve dok je l <=d i u svakom koraku ih delimo sa 2
// ako je leva granica na neparnoj poziciji dodajemo njenu vrednost na zbir i povećavamo granicu za 1
// ako je desna granica na parnoj poziciji dodajemo njenu vrednost na zbir i smanjujemo granicu za 1
// na kraju vraćamo zbir

int upit(int l, int d, vector<int>& stablo, int n) {
	int zbir = 0;
	for(l += n, d += n; l <= d; l /= 2, d /= 2) {
		if(l % 2 == 1) zbir += stablo[l++];
		if(d % 2 == 0) zbir += stablo[d--];
	}
	return zbir;
}

// prefiksno stablo čuvamo u nizu veličine prvi stepen dvojke veći ili jednak broju elemenata

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	int sn = velicina(n);
	vector<int> stablo = napravi_stablo(v, sn);
	while(true) {
		string komanda;
		cin >> komanda;
		if(komanda == "postavi") {
			int i, x;
			cin >> i >> x;
			postavi(i, x, stablo, sn);
		}
		else {
			int l, d;
			cin >> l >> d;
			cout << upit(l, d, stablo, sn) << endl;
		}
	}
	return 0;
}