#include <iostream>
#include <tuple>

using namespace std;

int mod(int a, int m) {
	return (m + a % m) % m;
}

// želimo da predstavimo nzd(a, b) preko a i b, tj. nzd(a, b) = a * x + b * y
// posmatramo niz ostataka pri deljenju i njihove linearne kombinacije:
//      prvi ostatak je prvi broj a = a * 1 + b * 0, pa je r1 = a, x1 = 1, x2 = 0
//      drugi ostatak je drugi broj b = a * 0 + b * 1, pa je r2 = b, x1 = 0, x2 = 1
//      dokle god je r2 veće od nule:
//          ostatak pri deljenju q trenutna dva ostatka je q = r1 / r2
//          r, x i y ažuriramo po formulama r1 = r2, r2 = r1 - q * r2
//  kada smo izašli iz petlje r2 je postalo 0, pa će rešenje biti poslednji nenula ostatak, odnosno r1
//  u x i y upisujemo vrednosti x1 i y1 i vraćamo r1
int euklid(int a, int b, int& x, int& y) {
	int r1 = a, r2 = b;
	int x1 = 1, y1 = 0;
	int x2 = 0, y2 = 1;
	while(r2 > 0) {
		int q = r1 / r2;
		tie(r1, r2) = make_pair(r2, r1 - q * r2);
		tie(x1, x2) = make_pair(x2, x1 - q * x2);
		tie(y1, y2) = make_pair(y2, y1 - q * y2);
	}
	x = x1;
	y = y1;
	return r1;
}

// rešava diofantovu jednačinu a * x + b * y = c
// Euklidovim algoritmom pronalazimo d = nzd(|a|, |b|), a u x i y upisujemo vrednosti tako da važi a * x + b * y = d
// ako d ne deli c onda jednačina nema rešenja i vraćamo false
// inače:
//      ako su x i y negativni pomnožimo ih sa -1
//      pomnožimo ih sa c/d i to su njihove konačne vrednosti
//      vraćamo true jer smo našli rešenje
bool diofant(int a, int b, int c, int& x, int& y) {
	int d = euklid(abs(a), abs(b), x, y);
	if(c % d != 0)
		return false;
	if(a < 0)
		x *= -1;
	if(b < 0)
		y *= -1;
	x *= c / d;
	y *= c / d;
	return true;
}

int main() {
	int a, c;
	cin >> a >> c;
	int t, y;
	if(diofant(a, 12, c, t, y))
		cout << "Sada je " << mod(t, 12) << " sati.\n";
	else
		cout << "Sat je baš pokvaren.\n";
	return 0;
}