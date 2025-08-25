#include <iostream>

using namespace std;

// vraća a mod m
// radimo a % m pa dodajemo m da ne bismo imali negativan broj, a potom opet modujemo sa m
int mod(int a, int m) {
	return (m + a % m) % m;
}

// sabiranje po modulu
int add(int a, int b, int m) {
	return mod(mod(a, m) + mod(b, m), m);
}

// oduzimanje po modulu
int sub(int a, int b, int m) {
	return mod(mod(a, m) - mod(b, m), m);
}

// množenje po modulu
int mul(int a, int b, int m) {
	return mod(mod(a, m) * mod(b, m), m);
}

// generisanje random brojeva:
//      prvi broj inicijalizujemo na npr. 1
//      dok god se ne dođe ponovo do broja 1:
//          pomnožimo trenutni broj sa a po modulu m
//          na tu vrednost dodamo c po modulu m
// za što više brojeva poželjno je odabrati prost broj m
int main() {
	int a = 10, c = 6, m = 19;
	int x = 1;
	do {
		x = add(mul(a, x, m), c, m);
		cout << x << ' ';
	} while(x != 1);
	cout << endl;
	return 0;
}