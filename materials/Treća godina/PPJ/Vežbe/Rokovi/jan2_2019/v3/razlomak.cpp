#include "razlomak.hpp"

using namespace std;

extern void yyerror(string s);

int nzd(int a, int b){
    while(b){
        int tmp = b;
        b = a%b;
        a = tmp;
    }

    return a;
}

Razlomak::Razlomak(int br, int im){
    if(im == 0){
        yyerror("Imenilac ne sme biti 0");
    }

    int d = nzd(abs(br), abs(im));
    br /= d;
    im /= d;

    if(im < 0){
        br = -br;
        im = -im;
    }

    brojilac = br;
    imenilac = im;
}

Razlomak::Razlomak(Razlomak& r){
    brojilac = r.brojilac;
    imenilac = r.imenilac;
}

void Razlomak::show(ostream& s){
    if(imenilac != 1){    
        s << "[" << brojilac << ", " << imenilac << "]";
    }else{
        s << "[" << brojilac << "]";
    }
}

Razlomak* Razlomak::operator +(Razlomak& r){
    int newBr = brojilac*r.imenilac + imenilac*r.brojilac;
    int newIm = imenilac * r.imenilac;
    
    int d = nzd(newBr, newIm);
    newBr /= d;
    newIm /= d;

    Razlomak* rez = new Razlomak(newBr, newIm);
    return rez;
}

Razlomak* Razlomak::operator -(Razlomak& r){
    int newBr = brojilac*r.imenilac - imenilac*r.brojilac;
    int newIm = imenilac * r.imenilac;
    
    int d = nzd(newBr, newIm);
    newBr /= d;
    newIm /= d;

    Razlomak* rez = new Razlomak(newBr, newIm);
    return rez;
}

Razlomak* Razlomak::operator *(Razlomak& r){
    int newBr = brojilac*r.brojilac;
    int newIm = imenilac*r.imenilac;

    int d = nzd(newBr, newIm);
    newBr /= d;
    newIm /= d;

    Razlomak* rez = new Razlomak(newBr, newIm);
    return rez;
}

Razlomak* Razlomak::operator /(Razlomak& r){
    int newBr = brojilac*r.imenilac;
    int newIm = imenilac*r.brojilac;

    int d = nzd(newBr, newIm);
    newBr /= d;
    newIm /= d;

    Razlomak* rez = new Razlomak(newBr, newIm);
    return rez;
}

int Razlomak::getBrojilac(){
    return brojilac;
}

int Razlomak::getImenilac(){
    return imenilac;
}

double Razlomak::vrednostFloat(){
    return (double)brojilac/(double)imenilac;
}

bool Razlomak::equals(Razlomak& r){
    int d = nzd(brojilac, imenilac);

    int newBr1 = brojilac/d;
    int newIm1 = imenilac/d;

    d = nzd(r.brojilac, r.imenilac);

    int newBr2 = r.brojilac/d;
    int newIm2 = r.imenilac/d;

    return brojilac == r.brojilac && imenilac == r.imenilac;
}


ostream& operator <<(ostream& s, Razlomak& r){
    r.show(s);
    return s;
}