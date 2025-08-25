#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Odrediti element niza sa najviše delilaca.

// uzimamo najveći element niza m
// algoritmom Eratostenovog sita računamo broj delilaca svih brojeva:
//      prolazimo redom kroz brojeve i od 1 do m
//      za svaki od njih prolazimo kroz umnoške i, 2i, 3i, ... dok ne dođemo do n i svima njima uvećamo broj delilaca za 1
// na kraju prolazimo kroz elemente niza i izvučemo onaj koji ima najviše delilaca
int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];

	int m = *max_element(begin(a), end(a));
	vector<int> d(m + 1);
	for(int i = 1; i <= m; i++)
		for(int j = i; j <= m; j += i)
			d[j]++;

	int maxd = 1;
	for(int x : a)
		if(d[x] > d[maxd])
			maxd = x;
	cout << maxd << ' ' << d[maxd] << endl;
	return 0;
}