#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//s^k je niska koja se dobija tako što se svaki karakter niske ponovi k puta. Npr. (abc)^3 = aaabbbccc. 
//Za date niske s i t odrediti najveće k tako da je s^k štucajuća podniska niske t, tj. 
//da karakteri niske s^k u nisci t ne moraju biti uzastupni ali moraju biti u istom redosledu kao u nisci s^k.
//Primer: s = abc, t = ababcabccabcbacbbcbca
//s^0 = "", jeste podniska
//s^1 = "abc", ABabCabccabcbacbbcbca, jeste podniska
//s^2 = "aabbcc", AbABcaBCCabcbacbbcbca, jeste podniska
//s^3 = "aaabbbccc", AbAbcABccaBcBaCbbCbCa, jeste podniska
//s^4 = "aaaabbbbcccc", nije podniska => k = 3

//Primetimo da je s^0 uvek podniska t, a za k = |t|/|s| + 1 niska s^k ima više karaktera od t pa ne može biti podniska
//Odatle zaključujemo da se rešenje nalazi u intervalu [1, |t|/|s|]
//Važi da ako je s^(k+1) podniska t onda je i s^k podniska t, pa možemo primeniti binarnu pretragu
//Funkcija će određivati da li za određenu dužinu iz datog intervala važi da je s^k podniska od t

bool stucajuciPodniz(const string& niz, const string& podniz, int k)
{
    int j = 0, b = 0;
    for (int i = 0; i < niz.size(); i++) //Prolazimo kroz nisku t
    {
        if (niz[i] == podniz[j]) //Ako smo našli pojavljivanje jednog karaktera podniske u nisci uvećavamo brojač
        {
            b++;
            if (b == k) //Ako je brojač dostigao k to znači da smo našli dovoljan broj pojavljivanja za to slovo
            {
                j++; //I onda prelazimo na sledeće slovo
                if (j == podniz.size()) //Ako smo došli do kraja niske s znači da smo proverili sva slova i s^k jeste podniska t
                    return true;
                b = 0;
            }
        }
    }
    return false; //U suprotnom s^k nije štucajuća podniska niske t
}

int main()
{
    string podniz, niz;
    cin >> podniz >> niz;
    int l = 1, d = niz.size() / podniz.size();
    while (l <= d)
    {
        int s = l + (d - l) / 2;
        if (stucajuciPodniz(niz, podniz, s))
            l = s + 1;
        else
            d = s - 1;
    }
    cout << d << endl;
    return 0;
}