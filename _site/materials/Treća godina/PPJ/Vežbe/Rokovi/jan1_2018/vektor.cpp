#include "vektor.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

extern void yyerror(string s);

double nzd(double a, double b){
    while(b){
        double tmp = b;
        b = fmod(a, b);
        a = tmp;
    }

    return a;
}

Vektor::Vektor(const Vektor& v){
    for(int i=0; i<v.koeficijenti.size(); i++){
        koeficijenti.push_back(v.koeficijenti[i]);
    }
}

void Vektor::dodajKoef(double v){
    koeficijenti.push_back(v);
}

Vektor* Vektor::operator +(Vektor& v) const{
    if(v.koeficijenti.size() != koeficijenti.size()){
        yyerror("Vektori nisu iste duzine(plus)");
    }
    
    Vektor* newVektor = new Vektor();

    for(int i=0; i<koeficijenti.size(); i++){
        newVektor->dodajKoef(koeficijenti[i] + v.koeficijenti[i]);
    }

    return newVektor;
}

Vektor* Vektor::operator -(Vektor& v) const{
    if(v.koeficijenti.size() != koeficijenti.size()){
        yyerror("Vektori nisu iste duzine(minus)");
    }
    
    Vektor* newVektor = new Vektor();

    for(int i=0; i<koeficijenti.size(); i++){
        newVektor->dodajKoef(koeficijenti[i] - v.koeficijenti[i]);
    }

    return newVektor;
}

Vektor* Vektor::operator *(double v) const{
    Vektor* newVektor = new Vektor();

    for(int i=0; i<koeficijenti.size(); i++){
        newVektor->dodajKoef(koeficijenti[i]*v);
    }

    return newVektor;
}

double Vektor::dot(Vektor& a, Vektor& b){
    if(a.koeficijenti.size() != b.koeficijenti.size())
        yyerror("Vektori nisu iste duzine (dot)");

    double rez = 0;
    for(int i=0; i<a.koeficijenti.size(); i++){
        rez += a.koeficijenti[i] * b.koeficijenti[i];
    }

    return rez;
}

double Vektor::kardinalnost() const{
    double rez = 0;
    for(int i=0; i<koeficijenti.size(); i++){
        rez += koeficijenti[i] * koeficijenti[i];
    }

    return sqrt(rez);
}

double Vektor::angle(Vektor& a, Vektor& b){
    double skalarni = dot(a, b);
    double norm_prod = a.kardinalnost() * b.kardinalnost();

    double rad = acos(skalarni / norm_prod);
    return rad*180/M_PI;
}

bool Vektor::ekvivalentni(Vektor& a, Vektor& b){
    if(a.koeficijenti.size() != b.koeficijenti.size())
        return false;

    double odnos = a.koeficijenti[0]/b.koeficijenti[0];

    for(int i=1; i<a.koeficijenti.size(); i++){
        if((a.koeficijenti[i]/b.koeficijenti[i]) != odnos)
            return false;
    }

    return true;
}

void Vektor::show(ostream& s) const{
    s << "<";
    for(int i=0; i<koeficijenti.size(); i++){
        if(i != 0)
            s << ",";
        s << koeficijenti[i];
    }
    s << ">";
}

ostream& operator <<(ostream& s, Vektor& vektor){
    vektor.show(s);
    return s;
}