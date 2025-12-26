#ifndef VEKTOR_HPP
#define VEKTOR_HPP

#include <iostream>

using namespace std;

class Vektor{
    private:
        double x;
        double y;

    public:
        Vektor(){};
        Vektor(double x1, double y1, double x2, double y2);
        Vektor(double a, double b);
        Vektor(Vektor* v);

        void show(ostream& s) const;

        Vektor* operator +(Vektor& v) const;
        Vektor* operator -(Vektor& v) const;
        Vektor* operator *(double skalar) const;
        Vektor* sim() const;
        Vektor* refx() const;
        Vektor* refy() const;
        Vektor* rot(double theta) const;
        double norm() const;
        static double angle(const Vektor& a, const Vektor& b);
};

ostream& operator <<(ostream& s, Vektor& vektor);

#endif