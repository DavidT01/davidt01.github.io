#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int mod(int a, int m) {
	return (m + a % m) % m;
}

int add(int a, int b, int m) {
	return mod(mod(a, m) + mod(b, m), m);
}

int sub(int a, int b, int m) {
	return mod(mod(a, m) - mod(b, m), m);
}

int mul(int a, int b, int m) {
	return mod(mod(a, m) * mod(b, m), m);
}

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

// funkcija računa inverz od a pod modulu m
// zapravo tražimo x tako da važi: a * x + m * k = 1
// pronađeno rešenje Diofantove jednačine vraćamo po modulu m
int inverz(int a, int m) {
	int x, k;
	diofant(a, m, 1, x, k);
	return mod(x, m);
}

// pronalazi broj x za koji važi: za svako as[i] i ns[i] važi: x mod ns[i] = as[i]
// kineska teorema o ostacima:
//      računamo N kao proizvod svih modula
//      inicijalizujemo rešenje na 0 i prolazimo kroz sve elemente vektora as, tj. desne strane svih jednačina:
//          računamo Ni kao N / ns[i], što je zapravo proizvod svih modula osim onog koji odgovara trenutno posmatranoj jednačini
//          računamo m: inverz Ni po modulu ns[i]
//          računamo proizvod as[i] * Ni * m po modulu N i dodajemo ga na trenutnu vrednost rešenja po modulu N
// vraćamo rešenje
int kto(vector<int>& as, vector<int>& ns) {
	int N = 1;
	for(int n : ns)
		N *= n;
	int x = 0;
	for(int i = 0; i < as.size(); i++) {
		int Ni = N / ns[i];
		int m = inverz(Ni, ns[i]);
		int t = mul(as[i], mul(Ni, m, N), N);
		x = add(x, t, N);
	}
	return x;
}

int main() {
	vector<int> as = {3, 4};
	vector<int> ns = {5, 7};
	cout << kto(as, ns) << endl;
	return 0;
}