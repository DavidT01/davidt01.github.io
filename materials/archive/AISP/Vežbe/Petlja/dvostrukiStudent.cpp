#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 50000

using namespace std;

//https://arena.petlja.org/competition/asp2021-domaci-1#tab_132065
//Složenost - O(nlogn + n) = O(nlogn)

struct Student {
    string ime;
    string prezime;
};

bool uporedi(const Student& a, const Student& b) { //Poredimo studente po imenu, ako su ista poredimo po prezimenu

    if (a.ime < b.ime) 
        return true;
    if (a.ime > b.ime) 
        return false;
    return a.prezime <= b.prezime;
}

int main() {

    int n = 0, k = 0;
    string ime, prezime;
    Student studenti[MAX];
    while (cin >> studenti[n].ime >> studenti[n].prezime) //Brojimo koliko je studenata učitano
        n++;
    sort(studenti, studenti + n, uporedi); //Koristimo našu funkciju za poređenje i sortiramo studente
    for (int i = 0; i < n - 1; i++) //Sada će se ponovljeno ime naći dva puta uzastopno, pronalazimo ga i ispisujemo na kraju
        if ((studenti[i].ime == studenti[i + 1].ime) && (studenti[i].prezime == studenti[i + 1].prezime)) {
            k = i;
            break;
        }
    cout << studenti[k].ime << " " << studenti[k].prezime << endl;
    return 0;
}