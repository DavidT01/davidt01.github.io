#include <iostream>
#include <vector>

using namespace std;

//Odrediti broj i zbir prostih brojeva iz intervala [a, b]. Ako je taj zbir veći od 10^6 ispisati poslednjih 6 cifara zbira

//Pomoću algoritma Eratostenovog sita odredićemo koji su prosti brojevi manji ili jednaki b
//Na kraju ćemo brojeve iz intervala [a, b] koji su prosti dodati na zbir po modulu 10^6 i uvećati brojač
//Složenost - O(log(log(b)) + (b - a)) =u najgorem slučaju= O(b)

void eratostenovoSito(vector<bool>& prost, int n) 
{
    prost.resize(n + 1, true);
    prost[0] = prost[1] = false;
    for (int i = 2; i * i <= n; i++)
        if (prost[i]) {
            for (int j = i * i; j <= n; j += i)
                prost[j] = false;
        }
}

int main() {
    int a, b;
    cin >> a >> b;
    vector<bool> prost;
    eratostenovoSito(prost, b);
    long zbir = 0, k = 0;
    for (int i = a; i <= b; i++)
        if (prost[i]) {
            zbir = (zbir + i) % 1000000;
            k++;
        }
    cout << k << " " << zbir << endl;
    return 0;
}