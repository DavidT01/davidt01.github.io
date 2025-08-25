#include <iostream>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/treci_obilazak

string postfiks(string prefiks, string infiks)
{
    if (prefiks == "")
        return "";
    char koren = prefiks[0];
    int duzinaLevo = infiks.find(koren);
    string prefiksLevo = prefiks.substr(1, duzinaLevo);
    string infiksLevo = infiks.substr(0, duzinaLevo);
    string prefiksDesno = prefiks.substr(1 + duzinaLevo);
    string infiksDesno = infiks.substr(1 + duzinaLevo);
    return postfiks(prefiksLevo, infiksLevo) + postfiks(prefiksDesno, infiksDesno) + koren;
}

int main()
{
    string prefiks, infiks;
    cin >> prefiks >> infiks;
    cout << postfiks(prefiks, infiks) << endl;
    return 0;
}