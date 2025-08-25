#ifndef VEKTOR_HPP
#define VEKTOR_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

class Vektor{
    private:
        vector<double> vektor;
    
    public:
        Vektor(){};
        Vektor(vector<double>& v);
        Vektor(Vektor& v);

        void show(ostream& s) const;

        void dodajKoef(double v);

        Vektor* operator +(Vektor& v) const;
        Vektor* operator -(Vektor& v) const;
        Vektor* operator *(double v) const;

        double norma(Vektor& v);
        double skalarniProizvod(Vektor& v1, Vektor& v2);

        double ugao(Vektor& v1, Vektor& v2);
        bool ekvivalencija(Vektor& v1, Vektor& v2);

};

ostream& operator <<(ostream& s, Vektor& vek);

#endif