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
        Razlomak(Razlomak& razlomak);

        void show(ostream& s);

        Razlomak* operator +(const Razlomak& r) const;
        Razlomak* operator -(const Razlomak& r) const;
        Razlomak* operator *(const Razlomak& r) const;
        Razlomak* operator /(const Razlomak& r) const;

        int getBrojilac();
        int getImenilac();
};

ostream& operator <<(ostream& s, Razlomak& razlomak);

#endif