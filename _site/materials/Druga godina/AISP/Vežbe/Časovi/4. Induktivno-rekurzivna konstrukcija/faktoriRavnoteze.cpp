// Дефинишимо висину празног дрвета као 0, а непразног дрвета као број чворова од корена тог дрвета до
// њему најудаљенијег листа (рачунајући и корен и тај лист). Дефинишимо фактор равнотеже чвора бинарног
// дрвета као апсолутну разлику између висина његовог левог и десног потомка. Напиши програм који одређује
// највећи фактор равнотеже неког чвора учитаног бинарног дрвета

#include <iostream>
#include <algorithm>

using namespace std;

struct Cvor {
    int vr;
    Cvor* levo;
    Cvor* desno;
};

void maxFaktorVisina(Cvor* koren, int& visina, int& maxFaktor) {
    if(koren == nullptr) {
        visina = maxFaktor = 0;
        return;
    }
    int visinaLevo, maxFaktorLevo, visinaDesno, maxFaktorDesno;
    maxFaktorVisina(koren->levo, visinaLevo, maxFaktorLevo);
    maxFaktorVisina(koren->desno, visinaDesno, maxFaktorDesno);
    int faktor = abs(visinaLevo - visinaDesno);
    maxFaktor = max({faktor, maxFaktorLevo, maxFaktorDesno});
    visina = 1 + max(visinaLevo, visinaDesno);
}

int main() {

    return 0;
}