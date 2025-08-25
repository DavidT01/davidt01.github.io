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

Razlomak::Razlomak(Razlomak& r){
    if(r.imenilac == 0){
        yyerror("Imenilac ne moze biti 0");
    }

    int d = nzd(max(r.brojilac, r.imenilac), min(r.brojilac, r.imenilac));

    brojilac = r.brojilac / d;
    imenilac = r.imenilac / d;
}

Razlomak::Razlomak(int br, int im){
    if(im == 0){
        yyerror("Imenilac ne moze biti 0");
    }

    int d = nzd(max(br, im), min(br, im));

    brojilac = br / d;
    imenilac = im / d;
}

void Razlomak::show(ostream& s) const{
    s << "[" << brojilac << ", " << imenilac << "]";
}

// 1 + 3  = 1*4 + 2 * 3 = 4+6 = 10 = 5
// 2   4        2*4        8     8   4

Razlomak* Razlomak::operator +(Razlomak& r){
    Razlomak* rez = new Razlomak();

    rez->brojilac = brojilac*r.imenilac + imenilac*r.brojilac;
    rez->imenilac = imenilac*r.imenilac;

    int d = nzd(rez->brojilac, rez->imenilac);

    rez->brojilac /= d;
    rez->imenilac /= d;

    return rez;
}

Razlomak* Razlomak::operator -(Razlomak& r){
    Razlomak* rez = new Razlomak();

    rez->brojilac = brojilac*r.imenilac - imenilac*r.brojilac;
    rez->imenilac = imenilac*r.imenilac;

    int d = nzd(rez->brojilac, rez->imenilac);

    rez->brojilac /= d;
    rez->imenilac /= d;

    return rez;
}

Razlomak* Razlomak::operator *(Razlomak& r){
    Razlomak* rez = new Razlomak();

    rez->brojilac = brojilac*r.brojilac;
    rez->imenilac = imenilac*r.imenilac;

    int d = nzd(rez->brojilac, rez->imenilac);

    rez->brojilac /= d;
    rez->imenilac /= d;

    return rez;
}

Razlomak* Razlomak::operator /(Razlomak& r){
    Razlomak* rez = new Razlomak();

    rez->brojilac = brojilac*r.imenilac;
    rez->imenilac = imenilac*r.brojilac;

    int d = nzd(rez->brojilac, rez->imenilac);

    rez->brojilac /= d;
    rez->imenilac /= d;

    return rez;
}

int Razlomak::getImenilac(){
    return imenilac;
}

int Razlomak::getBrojilac(){
    return brojilac;
}

double Razlomak::razlomakKaoDouble(){
    return (double)brojilac/(double)imenilac;
}

bool Razlomak::equals(Razlomak& r){
    int d = nzd(brojilac, imenilac);
    brojilac /= d;
    imenilac /= d;

    d = nzd(r.brojilac, r.imenilac);
    r.brojilac /= d;
    r.imenilac /= d;

    if(brojilac == r.brojilac && imenilac == r.imenilac)
        return true;
    
    return false;
}

ostream& operator <<(ostream& s, Razlomak& r){
    r.show(s);
    return s;
}