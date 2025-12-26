#include <iostream>
#include <stdlib.h>

using namespace std;

//Izračunati maksimalan faktor ravnoteže stabla. Faktor ravnoteže je apsolutna vrednost razlike
//visina levog i desnog podstabla nekog čvora.

void maxFaktor(Cvor* koren, int& visina, int& maxFaktor)
{
    if (koren == nullptr)
    {
        visina = 0;
        maxFaktor = 0;
        return;
    }
    int visinaLevo, maxFakorLevo;
    maxFaktor(koren->levo, visinaLevo, maxFaktorLevo);
    int visinaDesno, maxFaktorDesno;
    maxFaktor(koren->desno, visinaDesno, maxFaktorDesno);
    int faktor = abs(visinaLevo - visinaDesno);
    maxFaktor = max({ faktor, maxFaktorLevo, maxFaktorDesno });
    visina = 1 + max(visinaLevo, visinaDesno);
}

int main()
{
    //učitamo stablo
    int visina, maxFaktor;
    maxFaktor(koren, visina, maxFaktor);
    cout << maxFaktor << endl;
    //oslobodimo stablo
    return 0;
}