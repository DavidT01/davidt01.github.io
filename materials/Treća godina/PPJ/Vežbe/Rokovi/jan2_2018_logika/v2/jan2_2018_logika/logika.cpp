#include "logika.hpp"

using namespace std;

extern void yyerror(string s);

Logika::Logika(Logika& l){
    vrednosti = l.vrednosti;
}

Logika::Logika(int v){
    dodaj_vrednost(v);
}

int Logika::operator[] (int i){
    return vrednosti[i];
}
int Logika::size(){
    return vrednosti.size();
}

void Logika::dodaj_vrednost(int v){
    vrednosti.push_back(v);
}

void Logika::show(ostream& s){
    if(vrednosti[0] == 0){
        s << "False";
    }else if(vrednosti[0] == 1){
        s << "True";
    }else{
        s << "Undef";
    }
}

//   T F U
// T T F U
// F F F F 
// U U F U

// CONJ
Logika* Logika::operator +(Logika& l){
    Logika* rez = new Logika();

    if(vrednosti[0] == 1 && l.vrednosti[0] == 1){
        rez->dodaj_vrednost(1);
    }else if(vrednosti[0] == 2 || l.vrednosti[0] == 2){
        rez->dodaj_vrednost(2);
    }else{
        rez->dodaj_vrednost(0);
    }

    return rez;
}

//   T F U
// T T T T
// F T F U
// U T U U

// DISJ
Logika* Logika::operator -(Logika& l){
    Logika* rez = new Logika();

    if(vrednosti[0] == 1 || l.vrednosti[0] == 1){
        rez->dodaj_vrednost(1);
    }else if(vrednosti[0] == 0){
        rez->dodaj_vrednost(l.vrednosti[0]);
    }else if(l.vrednosti[0] == 0){
        rez->dodaj_vrednost(vrednosti[0]);
    }else{
        rez->dodaj_vrednost(2);
    }

    return rez;
}

// IMPL
Logika* Logika::operator !=(Logika& l){
    Logika* rez = new Logika();

    if(vrednosti[0] == 1){
        rez->dodaj_vrednost(l.vrednosti[0]);
    }else{
        rez->dodaj_vrednost(1);
    }

    return rez;
}


//   T F U
// T T F F
// F F T F
// U F F T

// EQ
Logika* Logika::operator ==(Logika& l){
    Logika* rez = new Logika();

    if(vrednosti[0] == l.vrednosti[0]){
        rez->dodaj_vrednost(1);
    }else{
        rez->dodaj_vrednost(0);
    }

    return rez;
}

Logika* Logika::operator !(){
    Logika* rez = new Logika();
    
    if(vrednosti[0] == 0){
        rez->dodaj_vrednost(1);
    }else if(vrednosti[0] == 1){
        rez->dodaj_vrednost(0);
    }else{
        rez->dodaj_vrednost(2);
    }

    return rez;
}

ostream& operator <<(ostream& s, Logika& l){
    l.show(s);
    return s;
}