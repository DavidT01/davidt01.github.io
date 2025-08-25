#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/pametna_kupovina_akcija

int akcije(int l, int d, vector<int>& v, int& vmax, int& vmin)
{
	if (l == d)
	{
		vmax = vmin = v[l];
		return 0;
	}
	int s = (l + d) / 2;
	int maxL, minL;
	int resL = akcije(l, s, v, maxL, minL);
	int maxD, minD;
	int resD = akcije(s + 1, d, v, maxD, minD);
	vmax = max(maxL, maxD);
	vmin = min(minL, minD);
	return max({ resL, resD, maxD - minL });
}

int main()
{
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	int vmax, vmin;
	cout << akcije(0, n - 1, v, vmax, vmin) << endl;
	return 0;
}