#include <iostream>
#include <string>
#include <vector>

using namespace std;

// na početku vektor inicijalizujemo na 0, a zatim krećemo od pozicije 1:
//      posmatramo dužinu prethodnog prefiks-sufiksa j (odnosno sa pozicije i - 1)
//      dok god je pozicija j veća od 0 i karakteri na pozicija i i j se razlikuju idemo unazad
//      tako što j ažuriramo na dužinu sufiks-prefiksa od j - 1, tj. j = p[j - 1]
//      ako je nakon petlje karakter na poziciji i jednak karakteru na poziciji j uvećamo j za 1
//      vrednost j smeštamo u p[i]
// na kraju vraćamo vektor
vector<int> kmp(string s) {
	int n = s.size();
	vector<int> p(n);
	for(int i = 1; i < n; i++) {
		int j = p[i - 1];
		while(j > 0 && s[i] != s[j])
			j = p[j - 1];
		if(s[i] == s[j])
			j++;
		p[i] = j;
	}
	return p;
}

// KMP algoritam nam vraća niz koji na poziciji i sadrži najduži prefiks-sufiks podniske od pozicije 0 do pozicije i
// string za koji ćemo računati je oblika "uzorak#tekst"
// na kraju prolazimo kroz taj string od mesta gde je taraba (uzorak.size()) i idemo do kraja niske
// ako je dužina prefiksa-sufiksa na poziciji i jednaka dužini uzorka ispisujemo tu poziciju
// pogodak koji smo našli se nalazi na poslednjem karakteru podniske koja je jednaka uzorku,
// pa originalni indeks dobijamo kada dva puta oduzmemo dužinu uzorka
// jednom jer smo na početak modifikovanog stringa dodali uzorak i drugi da bismo sa kraja pronađenog pogotka došli na početak
int main() {
	string s, t;
	cin >> s >> t;
	string p = s + "#" + t;
	vector<int> ps = kmp(p);
	for(int i = s.size(); i < p.size(); i++)
		if(ps[i] == s.size())
			cout << i - 2 * s.size() << ' ';
	cout << endl;
	return 0;
}