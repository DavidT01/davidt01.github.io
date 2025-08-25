#include "vektor.hpp"

using namespace std;

extern void yyerror(string s);

Vektor::Vektor(vector<double>& v){
    vektor = v;
}

Vektor::Vektor(Vektor& v){
    vektor = v.vektor;
}

void Vektor::show(ostream& s) const{
    s << "<";

    for(int i=0; i<vektor.size(); i++){
        if(i != 0)
            s << ", ";
        s << vektor[i];
    }

    s << ">";
}

void Vektor::dodajKoef(double v){
    vektor.push_back(v);
}

Vektor* Vektor::operator +(Vektor& v) const{
    if(vektor.size() != v.vektor.size())
        yyerror("Ne mogu se sabirati vektori koji nisu istih velicina");

    Vektor* noviVek = new Vektor();

    for(int i=0; i<vektor.size(); i++){
        noviVek->vektor.push_back(vektor[i] + v.vektor[i]);
    }

    return noviVek;
}

Vektor* Vektor::operator -(Vektor& v) const{
    if(vektor.size() != v.vektor.size())
        yyerror("Ne mogu se oduzimati vektori koji nisu istih velicina");

    Vektor* noviVek = new Vektor();

    for(int i=0; i<vektor.size(); i++){
        noviVek->vektor.push_back(vektor[i] - v.vektor[i]);
    }

    return noviVek;
}

Vektor* Vektor::operator *(double v) const{
    Vektor* noviVek = new Vektor();
    
    for(int i=0; i<vektor.size(); i++){
        noviVek->vektor.push_back(v*vektor[i]);
    }

    return noviVek;
}

double Vektor::norma(Vektor& v){
    double rez = 0;
    
    for(int i=0; i<v.vektor.size(); i++){
        rez += v.vektor[i] * v.vektor[i];
    }

    return sqrt(rez);
}

double Vektor::skalarniProizvod(Vektor& v1, Vektor& v2){
    if(v1.vektor.size() != v2.vektor.size())
        yyerror("Ne moze skalarni proizvod vektora razlicitih velicina");
    
    double rez = 0;

    for(int i=0; i<v1.vektor.size(); i++){
        rez += v1.vektor[i] * v2.vektor[i];
    }

    return rez;
}

double Vektor::ugao(Vektor& v1, Vektor& v2){
    double normv1 = norma(v1);
    double normv2 = norma(v2);

    double norm = normv1*normv2;
    double dot = skalarniProizvod(v1, v2);

    double valInRadians = acos(dot/norm);

    return valInRadians*180/M_PI;
}

bool Vektor::ekvivalencija(Vektor& v1, Vektor& v2){
    if(v1.vektor.size() != v2.vektor.size())
        yyerror("Vektori razlicitih velicina nisu ekvivalentni");
    
    double odnos = v2.vektor[0] / v1.vektor[0];

    for(int i=0; i<v1.vektor.size(); i++){
        if(odnos*v1.vektor[i] != v2.vektor[i])
            return false;
    }

    return true;
}

ostream& operator <<(ostream& s, Vektor& vek){
    vek.show(s);
    return s;
}