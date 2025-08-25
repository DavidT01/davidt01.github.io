#include "logika.hpp"

using namespace std;

Logika::Logika(int v){
    vrednost = v;
}

Logika::Logika(Logika& l){
    vrednost = l.vrednost;
}

void Logika::show(ostream& s) const{
    if(vrednost == 0){
        s << "False";
    }else if(vrednost == 1){
        s << "True";
    }else{
        s << "Undef";
    }
}

//    T F U
//  T T F U
//  F F F F
//  U U F U

// konjukcija
Logika* Logika::operator +(Logika& l){
    if(vrednost == 1 && l.vrednost == 1){
        return new Logika(1);
    }else if(vrednost == 0 || l.vrednost == 0){
        return new Logika(0);
    }else{
        return new Logika(2);
    }
}

//    T F U
//  T T T T
//  F T F U
//  U T U U

// disjunkcija
Logika* Logika::operator -(Logika& l){
    if(vrednost == 1 || l.vrednost == 1){
        return new Logika(1);
    }else if(vrednost == 0 && l.vrednost == 0){
        return new Logika(0);
    }else{
        return new Logika(2);
    }
}

// implikacija
Logika* Logika::operator /(Logika& l){

}

// ekvivalencija
Logika* Logika::operator %(Logika& l){

}

Logika* Logika::operator !(){
    if(vrednost == 2){
        return new Logika(2);
    }else if(vrednost == 1){
        return new Logika(0);
    }else{
        return new Logika(1);
    }
}

ostream& operator <<(ostream& s, Logika& l){
    l.show(s);
    return s;
}