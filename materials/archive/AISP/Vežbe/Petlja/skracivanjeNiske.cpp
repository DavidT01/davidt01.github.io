#include <iostream>
#include <string>

using namespace std;

//https://arena.petlja.org/sr-Latn-RS/competition/asp2021-domaci-2#tab_134056

//Tehnikom dva pokazivača prolazimo kroz obe niske i proveravamo jednakost karaktera
//Složenost - O(n)

int main() {
    string s1, s2;
    cin >> s1;
    s2 += s1[0]; //Dodajemo prvi karakter početne niske u krajnju nisku
    int i = 1, j = 0; //i je pokazivač za početnu, a j za krajnju nisku
    while (i < s1.size()) 
    {
        if (s1[i] != s2[j]) //Ako je sledeći karakter u našoj nisci različit od prethodno dodatog u krajnju, dodajemo i novi
        {
            s2 += s1[i];
            i++;
            j++;
        }
        else //Ako su isti onda ćemo skinuti poslednji karakter sa krajnje niske(jer će se on poništiti sa novim)
        {
            s2.pop_back();
            j--; 
            i++;
        }
    }
    cout << s2 << endl;
    return 0;
}