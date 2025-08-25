#ifndef VEKTOR_HPP
#define VEKTOR_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Vektor{
    private:
        double x;
        double y;
    public:
        Vektor(){};
        Vektor(double a, double b);
        Vektor(Vektor& v);
        Vektor(double x1, double y1, double x2, double y2);

        void show(ostream& s) const;

        Vektor* operator +(Vektor& v);
        Vektor* operator -(Vektor& v);
        Vektor* operator -();
        Vektor* operator *(double skalar);
        Vektor* sim();
        Vektor* refx();
        Vektor* refy();
        Vektor* rot(double angle);
        double norm();
        static double angle(Vektor& v1, Vektor& v2);
};

ostream& operator <<(ostream& s, Vektor& v);

#endif