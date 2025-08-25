#ifndef UGAO_HPP
#define UGAO_HPP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Vektor{
    private:
        vector<double> koeficijenti;
    
    public:
        Vektor(){};
        Vektor(const Vektor& v);

        void dodajKoef(double v);

        Vektor* operator +(Vektor& v) const;
        Vektor* operator -(Vektor& v) const;
        Vektor* operator *(double v) const;
        
        static double dot(Vektor& a, Vektor& b);
        double kardinalnost() const;
        static double angle(Vektor& a, Vektor& b);

        static bool ekvivalentni(Vektor& a, Vektor& b);

        void show(ostream& s) const;
};

ostream& operator <<(ostream& s, Vektor& vektor);

#endif