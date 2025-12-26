#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// svaki čvor sada sadrži i vrednost (kao u segmentnom drvetu) ali i koeficijent propagacije
// ako je koeficijent propagacije različit od 0 to znači da se vrednost treba uvećati za taj koeficijent
// onoliko puta koliko elemenata niza pokriva segment posmatranog čvora, na početku se koeficijent propagacije
// postavlja na 0

struct cvor {
	int vrednost = 0;
	int uvecanje = 0;
};

// funkcija koja računa stepen dvojke veći ili jednak n (kao kod segmentnih)

int velicina(int n) {
	return pow(2, ceil(log2(n)));
}

// stablo formiramo tako što prekopiramo elemente niza od pozicije n, a onda ostale pozicije od n - 1 do 1
// računamo po formuli kao i kod segmentnih stabala

vector<cvor> napravi_stablo(vector<int>& niz, int n) {
	vector<cvor> stablo(2 * n);
	for(int i = 0; i < niz.size(); i++)
		stablo[n + i].vrednost = niz[i];
	for(int i = n - 1; i > 0; i--)
		stablo[i].vrednost = stablo[2 * i].vrednost + stablo[2 * i + 1].vrednost;
	return stablo;
}

// funkcija izvršava lenju propagaciju, tj. čvor i koji pokriva elemente od pozicije tl do td uvećava za njegovo uvećanje:
//      na vrednost čvora dodaje koeficijent propagacije pomnožen sa brojem elemenata koje pokriva (td - tl + 1)
//      ako čvor nije list (tl < td), ažuriramo koeficijent propagacije njegove dece
//      postavimo koeficijent propagacije čvora i na 0 jer je on ažuriran

void propagiraj(int i, int tl, int td, vector<cvor>& stablo) {
	stablo[i].vrednost += stablo[i].uvecanje * (td - tl + 1);
	if(tl < td) {
		stablo[2 * i].uvecanje += stablo[i].uvecanje;
		stablo[2 * i + 1].uvecanje += stablo[i].uvecanje;
	}
	stablo[i].uvecanje = 0;
}

// posmatramo trenutni čvor idx, koji pokriva segment [tl, td]:
//		ako je koeficijent propagacije različit od 0 izvršavamo propagaciju
//		ako se segmenti [l, d] i [tl, td] mimoilaze ne radimo ništa
//		ako se segment [tl, td] potpuno sadrži u [l, d]:
//			uvećavamo koef. propagacije trenutnog čvora idx za onoliko koliko treba uvećati elemente segmenta [l, d]
//			izvršimo propagaciju čvora idx
//		inače, ako se ova dva segmenta seku:
//			računamo središnju poziciju trenutnog segmenta [tl, td]
//			rekurzivno pokrećemo uvećavanje za njegovu decu:
//				levo dete je 2 * idx i pokriva segment [tl, s]
//				desno dete je 2 * idx + 1 i pokriva segment [s + 1, td]
//			vrednost trenutnog čvora ažuriramo kao zbir vrednosti njegove dece

void uvecaj(int l, int d, int uvecanje, int idx, int tl, int td, vector<cvor>& stablo) {
	if(stablo[idx].uvecanje != 0)
		propagiraj(idx, tl, td, stablo);
	if(l > td || d < tl) return;
	if(tl >= l && td <= d) {
		stablo[idx].uvecanje += uvecanje;
		propagiraj(idx, tl, td, stablo);
	}
	else {
		int s = (tl + td) / 2;
		uvecaj(l, d, uvecanje, 2 * idx, tl, s, stablo);
		uvecaj(l, d, uvecanje, 2 * idx + 1, s + 1, td, stablo);
		stablo[idx].vrednost = stablo[2 * idx].vrednost + stablo[2 * idx + 1].vrednost;
	}
}

// posmatramo trenutni čvor idx, koji pokriva segment [tl, td]:
//		ako je koeficijent propagacije različit od 0 izvršavamo propagaciju
//		ako se segmenti [l, d] i [tl, td] mimoilaze udeo u konačnom zbiru je 0
//		ako se segment [tl, td] potpuno sadrži u [l, d] vraćamo vrednost u trenutnom čvoru idx
//		inače, ako se ova dva segmenta seku:
//			računamo središnju poziciju trenutnog segmenta [tl, td]
//			rekurzivno pokrećemo upit za njegovu decu:
//				levo dete je 2 * idx i pokriva segment [tl, s]
//				desno dete je 2 * idx + 1 i pokriva segment [s + 1, td]
//			vraćamo zbir vrednosti dobijenih od ova dva poziva

int upit(int l, int d, int idx, int tl, int td, vector<cvor>& stablo) {
	if(stablo[idx].uvecanje != 0)
		propagiraj(idx, tl, td, stablo);
	if(l > td || d < tl)
        return 0;
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
		if(operacija == "uvecaj") {
			int l, d, u;
			cin >> l >> d >> u;
			uvecaj(l, d, u, 1, 0, n - 1, stablo);
		}
		else if(operacija == "upit") {
			int l, d;
			cin >> l >> d;
			cout << upit(l, d, 1, 0, n - 1, stablo) << endl;
		}
	}
	return 0;
}