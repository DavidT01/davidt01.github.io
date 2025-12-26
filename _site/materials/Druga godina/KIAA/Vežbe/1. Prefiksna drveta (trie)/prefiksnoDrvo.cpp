#include <iostream>
#include <map>

using namespace std;

// čvor sadrži bool vrednost koja označava da li je tu kraj reči ili ne,
// kao i mapu gde je prva vrednost karakter a druga čvor do kog vodi grana preko
// tog karaktera

struct Cvor {
	bool kraj_reci;
	map<char, Cvor*> prelaz;
};

// prolazimo kroz sve karaktere stringa koji želimo da dodamo
// ako u mapi potomaka ne nalazimo granu sa tim karakterom pravimo novi čvor
// koren postavljamo na sledeći potomak
// na kraju označimo da je kraj reči

void dodaj(Cvor* koren, string& s) {
	for(char c : s) {
		if(koren->prelaz.find(c) == koren->prelaz.end())
			koren->prelaz[c] = new Cvor();
		koren = koren->prelaz[c];
	}
	koren->kraj_reci = true;
}

// prolazimo kroz sve karaktere stringa koji želimo da nađemo
// ako u mapu potomaka ne postoji traženi karakter vraćamo false
// prelazimo na sledeći potomak
// na kraju vraćamo bool vrednost koja govori da li se tu nalazi kraj reči

bool nadji(Cvor* koren, string& s) {
	for(char c : s) {
		if(koren->prelaz.find(c) == koren->prelaz.end())
			return false;
		koren = koren->prelaz[c];
	}
	return koren->kraj_reci;
}

// prolazimo kroz sve potomke i rekurzivno ih oslobađamo
// na kraju obrišemo sam koren

void oslobodi(Cvor* koren) {
	for(auto podstablo : koren->prelaz)
		oslobodi(podstablo.second);
	delete koren;
}

// proveravamo da li smo došli do kraja reči i ako jesmo ispisujemo je
// prolazimo kroz sve grane čvora i redom:
//      dodajemo sledeći karakter
//      ispisujemo rekurzivno reč sa tim karakterom
//      skidamo taj karakter

void ispisi(Cvor* koren, string& rec) {
	if(koren->kraj_reci)
		cout << rec << endl;
	for(auto podstablo : koren->prelaz) {
		rec.push_back(podstablo.first);
		ispisi(podstablo.second, rec);
		rec.pop_back();
	}
}

void ispisiObrnuto(Cvor* koren, string& rec) {
	if(koren->kraj_reci)
		cout << rec << endl;
	for(auto it = koren->prelaz.rbegin(); it != koren->prelaz.rend(); it++) {
		rec.push_back(it->first);
		ispisi(it->second, rec);
		rec.pop_back();
	}
}

// Zadatak: odrediti najveći zajednički prefiks skupa niski
// Rešenje: dodamo sve niske u trie drvo
//          na početku postavimo prefiks na praznu nisku
//          dok god nismo došli do kraja reči i dok god postoji samo jedan potomak:
//              uzimamo iterator na početak
//              dodajemo karakter na prefiks, a koren postavljamo na sledeći čvor

string nzp(Cvor* koren) {
	string prefiks = "";
	while(koren->prelaz.size() == 1 && !koren->kraj_reci) {
		auto it = koren->prelaz.begin();
		prefiks += it->first;
		koren = it->second;
	}
	return prefiks;
}

int main() {
	Cvor* stablo = new Cvor();
	string komanda, argument, rec = "";
	while(true) {
		cin >> komanda >> argument;
		if(komanda == "dodaj")
			dodaj(stablo, argument);
		else if(komanda == "nadji")
			cout << nadji(stablo, argument) << endl;
		else if(komanda == "prefiks")
			cout << nzp(stablo) << endl;
		else if(komanda == "ispis1")
			ispisi(stablo, rec);
		else if(komanda == "ispis2")
			ispisiObrnuto(stablo, rec);
		else
			break;
	}
	oslobodi(stablo);
	return 0;
}