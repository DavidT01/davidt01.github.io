#ifndef RAZLOMAK_HPP
#define RAZLOMAK_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

class Razlomak{
    private:
        int brojilac;
        int imenilac;
    
    public:
        Razlomak(){};
        Razlomak(Razlomak& r);
        Razlomak(int br, int im);

        void show(ostream& s) const;

        Razlomak* operator +(Razlomak& r);
        Razlomak* operator -(Razlomak& r);
        Razlomak* operator *(Razlomak& r);
        Razlomak* operator /(Razlomak& r);

        int getImenilac();
        int getBrojilac();

        double razlomakKaoDouble();
        bool equals(Razlomak& r);
};

ostream& operator <<(ostream& s, Razlomak& r);

#endif