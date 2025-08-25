#ifndef RAZLOMAK_HPP
#define RAZLOMAK_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

class Razlomak{
    private:
        int brojilac, imenilac;
    
    public:
        Razlomak(){};
        Razlomak(int br, int im);
        Razlomak(Razlomak& r);

        void show(ostream& s);

        Razlomak* operator +(Razlomak& r);
        Razlomak* operator -(Razlomak& r);
        Razlomak* operator *(Razlomak& r);
        Razlomak* operator /(Razlomak& r);

        int getBrojilac();
        int getImenilac();

        double vrednostFloat();
        bool equals(Razlomak& r);
};

ostream& operator <<(ostream& s, Razlomak& r);

#endif