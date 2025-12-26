#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// tačka (x, y)
using point = pair<int, int>;

// pravi vektor AB od tačaka A i B, AB = (b.x - a.x, b.y - a.y)
point vektor(point a, point b) {
	return {b.first - a.first, b.second - a.second};
}

// skalarni proizvod, u o v = u.x * v.x + u.y * v.y
int skalarniP(point u, point v) {
	return u.first * v.first + u.second * v.second;
}

// vektorski proizvod, u x v = u.x * v.y - u.y * v.x
int vektorskiP(point u, point v) {
	return u.first * v.second - u.second * v.first;
}

// orijentacija tačaka ABC, orijentacija = AB x AC
int orijentacija(point a, point b, point c) {
	return vektorskiP(vektor(a, b), vektor(a, c));
}

// kolinearnost tačaka ABC, ako im je orijentacija 0 tačke su kolinearne
bool kolinearne(point a, point b, point c) {
	return orijentacija(a, b, c) == 0;
}

// proverava pripadnost tačke X trouglu ABC
// ako su orijentacije trouglova ABX, BCX i CAX ili sve pozitivne ili sve negativne tačka pripada trouglu, a inače ne
// ukoliko koristimo >= i <= dozvoljavamo da se tačka X nalazi i na nekoj od stranica
bool pripadaTrouglu(point a, point b, point c, point x) {
	if(orijentacija(a, b, x) >= 0 && orijentacija(b, c, x) >= 0 && orijentacija(c, a, x) >= 0)
		return true;
	if(orijentacija(a, b, x) <= 0 && orijentacija(b, c, x) <= 0 && orijentacija(c, a, x) <= 0)
		return true;
	return false;
}

// proverava konveksnost mnogougla
// mnogougao je konveksan ako su mu sve trojke tačaka ili pozitivno ili negativno orijentisane
// prolazimo kroz sve trojke tačaka i, j, k i proveravamo da li se pojavljuje trojka sa negativnom i trojka sa pozitivno orijentacijom
// ako smo pronašli i neku trojku sa negativnom i neku trojku sa pozitivnom orijentacijom vraćamo false, a inače true
bool konveksan(vector<point>& p) {
	bool pos = false, neg = false;
	for(int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		int k = (i + 2) % p.size();
		if(orijentacija(p[i], p[j], p[k]) > 0)
			pos = true;
		if(orijentacija(p[i], p[j], p[k]) < 0)
			neg = true;
	}
	return !(pos && neg);
}

// formira prost mnogougao od zadatih tačaka
// u rezultujući vektor kopiramo dati vektor tačaka
// za nultu tačku postavimo tačku sa najmanjom x i y koordinatom
// preostalih n - 1 tačaka sortiramo prema nultoj tački T:
//		tačka A treba da bude pre tačke B ako je orijentacija TAB pozitivna
// na kraju vraćamo sortirani vektor tačaka
vector<point> makeSimple(vector<point>& pts) {
	vector<point> p = pts;
	swap(p[0], *min_element(begin(p), end(p)));
	sort(begin(p) + 1, end(p), [&](point a, point b) {
									return orijentacija(p[0], a, b) > 0;
							   });
	return p;
}

// Džarvisov algoritam (algoritam pakovanja poklona) za određivanje konveksnog omotača skupa tačaka
vector<int> jarvisHull(vector<point>& p) {
	vector<int> hull;
	int t = min_element(begin(p), end(p)) - begin(p);
	do {
		hull.push_back(t);
		int nt = (t + 1) % p.size(); // treba uzeti bilo koju tacku razlicitu od t
		for(int i = 0; i < p.size(); i++)
			if(orijentacija(p[t], p[i], p[nt]) > 0)
				nt = i;
		t = nt;
	} while(t != hull[0]);
	return hull;
}

// Grejemov algoritam za određivanje konveksnog omotača skupa tačaka
// nulta tačka će uvek biti deo konveksnog omotača pa je postavljamo za prvu u nizu tačaka
// ostale tačke u vektoru sortiramo prema orijentaciji u odnosu na nultu tačku
// u vektoru hull ćemo čuvati indekse tačaka koje želimo u omotaču
// nulta tačka uvek pripada omotaču pa je odmah dodajemo u taj vektor
// prolazimo kroz sve ostale tačke od 1 do kraja:
//		sa omotača skidamo tačke sve dok je orijentacija poslednje dve tačke omotača i tačke i negativna
//		to možemo da radimo dokle god imamo više od 1 tačke (jer ne želimo da ikad skinemo nultu tačku)
//		pretpostlednja tačka je p[hull[hull.size() - 2]], a poslednja tačka omotača je p[hull[hull.size() - 1]]
//		nakon skidanja svih tačaka postavljamo i-tu tačku na omotač
// na kraju vraćamo vektor hull koji sadrži indekse tačaka koje se nalaze u omotaču
vector<int> grahamHull(vector<point>& p) {
	swap(p[0], *min_element(begin(p), end(p)));
	sort(begin(p) + 1, end(p), [&](point a, point b) {
									return orijentacija(p[0], a, b) > 0;
							   });
	vector<int> hull = {0};
	for(int i = 1; i < p.size(); i++) {
		while(hull.size() > 1 && orijentacija(p[hull[hull.size() - 2]], p[hull[hull.size() - 1]], p[i]) < 0)
			hull.pop_back();
		hull.push_back(i);
	}
	return hull;
}

// proverava da li se tačka T nalazi u konveksnom mnogouglu P
// posmatramo tačke od prve (preskačemo nultu) do zadnje i tražimo tačku veću ili jednaku T, tačke se porede po orijentaciji i koristi se binarna pretraga (lower bound)
// ako iterator pokazuje na end(p) tačka nije pronađena i vraćamo false jer se T onda ne nalazi u mnogouglu
// inače uzimamo poziciju i pronađene tačke
// ispitamo da li se tačka t nalazi u trouglu p[0], p[i - 1], p[i] i ako se nalazi vraćamo true, a inače false
bool inConvex(point t, vector<point>& p) {
	auto it = lower_bound(begin(p) + 1, end(p), t, [&](point a, point b) {
														return orijentacija(p[0], a, b) > 0;
												   });
	if(it == end(p))
		return false;
	int i = it - begin(p);
	return pripadaTrouglu(p[0], p[i - 1], p[i], t);
}

// orijentisana površina trougla ABC jednaka je polovini orijentacije trougla
float orijentisanaPovrsina(point a, point b, point c) {
	return orijentacija(a, b, c) * 0.5f;
}

// orijentisana površina mnogougla jednaka je zbiru orijentisanih površina svih trojki tačaka:
//		polazimo od treće tačke, idemo do zadnje i gledamo sve trojke tačaka
//		računamo orijentisanu površinu trougla koji one grade i dodajemo je na ukupnu
//		na kraju vraćamo ukupnu orijentisanu površinu
float orijentisanaPovrsina(vector<point>& p) {
	float a = 0;
	for(int i = 2; i < p.size(); i++)
		a += orijentisanaPovrsina(p[0], p[i - 1], p[i]);
	return a;
}

int main() {
	return 0;
}