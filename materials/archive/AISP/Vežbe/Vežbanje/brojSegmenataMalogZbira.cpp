// https://arena.petlja.org/competition/asp-rokovi-1#tab_133922

#include <iostream>
#include <vector>

using namespace std;

int main(){
	
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n ;i++)
		cin >> a[i];
	int t; cin >> t;
	
	int glavna_suma = 0;
	int petlja_suma = 0;
	int broj_brojeva = 0;
	int v = 1;
	int j = 0;
	for(int i = 0; i < n ;i++) {

		petlja_suma += a[i];
		broj_brojeva += 1;
		
		if((i == n - 1 && t > petlja_suma) || (petlja_suma >= t)) {
			if(v) {
				glavna_suma += broj_brojeva * (broj_brojeva - 1)/2;
				v = 0;
			}
			while(t <= petlja_suma){
                petlja_suma -= a[j];
                j++;
                broj_brojeva -= 1;
			}
			
			glavna_suma+=broj_brojeva;
			
			if(petlja_suma == 0)
				v = 1;
		}
	}

	cout << glavna_suma;	

	return 0;
}