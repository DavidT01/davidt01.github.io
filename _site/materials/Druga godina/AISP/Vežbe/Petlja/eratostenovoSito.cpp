#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka3/eratostenovo_sito

//Funkcija popunjava niz od n + 1 elemenata na sledeći način:
//Broj i je prost => prost[i] = true, inače prost[i] = false
//Složenost - O(log(logn))

void eratostenovoSito(vector<bool>& prost, int n) 
{
    prost.resize(n + 1, true);
    prost[0] = prost[1] = false; //Brojevi 0 i 1 nisu prosti
    for (int i = 2; i * i <= n; i++) //Idemo od 2 do sqrt(n)
        if (prost[i]) { //Ako je i prost svi njegovi umnošci nisu, pa ih odmah stavljamo na false
            for (int j = i * i; j <= n; j += i)
                prost[j] = false;
        }
}

//Za sve brojeve manje ili jednake od b odredimo da li su prosti pomoću prethodne funkcije
//Potom sve koji su prosti i iz intervala [a, b] dodajemo na krajnji zbir
//Pri prolasku od a do b složenost najgoreg slučaja(a = 0) će biti linearna
//Ukupna složenost - O(log(logn)) + O(n) = O(n)

int main() {
    int a, b;
    cin >> a >> b;
    vector<bool> prost;
    eratostenovoSito(prost, b);
    int zbir = 0, k = 0;
    for (int i = a; i <= b; i++)
        if (prost[i]) {
            zbir = (zbir + i) % 1000000;
            k++;
        }
    cout << k << " " << zbir << endl;
    return 0;
}