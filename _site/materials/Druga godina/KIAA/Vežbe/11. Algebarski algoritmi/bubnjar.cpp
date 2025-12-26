#include <iostream>
#include <tuple>

using namespace std;

// Bubnjar udara levom rukom svakih a sekundi i desnom rukom svakih b sekundi. Za n datih upita, pronaći najmanju razliku među udarcima,
// kao i koji je to po redu udarac levom, a koji po redu desnom rukom u tom trenutku.

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

// najmanja razlika u udarcima je nzd(a, b) sekundi, pa pozivamo Euklidov algoritam da nađemo tu vrednost
// dobijamo ax + by = d, d je najmanja razlika, min(ax, by) je udarac levom, a max(ax, by) desnom rukom
int main() {
	int n;
	cin >> n;
	while(n--) {
		int a, b;
		cin >> a >> b;
		int x, y;
		int d = euklid(a, b, x, y);
		int t1 = min(abs(a * x), abs(b * y));
		int t2 = max(abs(a * x), abs(b * y));
		cout << d << ' ' << t1 << ' ' << t2 << endl;
	}
	return 0;
}