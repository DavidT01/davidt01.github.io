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
        yyerror("Imenilac ne sme biti 0.");
    }

    int d = nzd(max(br, im), min(br, im));
    brojilac = br/d;
    imenilac = im/d;
}

Razlomak::Razlomak(Razlomak& razlomak){
    if(razlomak.imenilac == 0){
        yyerror("Imenilac ne sme biti 0.");
    }

    int d = nzd(max(razlomak.brojilac, razlomak.imenilac), min(razlomak.brojilac, razlomak.imenilac));
    brojilac = razlomak.brojilac/d;
    imenilac = razlomak.imenilac/d;
}

void Razlomak::show(ostream& s){
    if(imenilac == 1){
        s << "[" << brojilac << "]";
    }
    if(imenilac == -1){
        s << "[" << -1*brojilac << "]";
    }else{
        s << "[" << brojilac << ", " << imenilac << "]";
    }
}

Razlomak* Razlomak::operator +(const Razlomak& r) const{
    int newBrojilac = brojilac*r.imenilac + imenilac*r.brojilac;
    int newImenilac = imenilac*r.imenilac;

    int d = nzd(newBrojilac, newImenilac);

    newBrojilac /= d;
    newImenilac /= d;

    return new Razlomak(newBrojilac, newImenilac);
}

Razlomak* Razlomak::operator -(const Razlomak& r) const{
    int newBrojilac = brojilac*r.imenilac - imenilac*r.brojilac;
    int newImenilac = imenilac*r.imenilac;

    int d = nzd(newBrojilac, newImenilac);

    newBrojilac /= d;
    newImenilac /= d;

    return new Razlomak(newBrojilac, newImenilac);
}

Razlomak* Razlomak::operator *(const Razlomak& r) const{
    int newBrojilac = brojilac*r.brojilac;
    int newImenilac = imenilac*r.imenilac;

    int d = nzd(newBrojilac, newImenilac);

    newBrojilac /= d;
    newImenilac /= d;

    return new Razlomak(newBrojilac, newImenilac);
}

Razlomak* Razlomak::operator /(const Razlomak& r) const{
    int newBrojilac = brojilac*r.imenilac;
    int newImenilac = imenilac*r.brojilac;

    int d = nzd(newBrojilac, newImenilac);

    newBrojilac /= d;
    newImenilac /= d;

    return new Razlomak(newBrojilac, newImenilac);
}

int Razlomak::getBrojilac(){
    return brojilac;
}

int Razlomak::getImenilac(){
    return imenilac;
}

ostream& operator <<(ostream& s, Razlomak& razlomak){
    razlomak.show(s);
    return s;
}