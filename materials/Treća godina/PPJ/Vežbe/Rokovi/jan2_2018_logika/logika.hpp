#ifndef LOGIKA_HPP
#define LOGIKA_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

class Logika{
    private:
        int vrednost; // 0 false 1 true 2 undef
    public:
        Logika(){};
        Logika(int v);
        Logika(Logika& l);

        void show(ostream& s) const;

        // konjukcija
        Logika* operator +(Logika& l);
        // disjunkcija
        Logika* operator -(Logika& l);
        // implikacija
        Logika* operator /(Logika& l);
        // ekvivalencija
        Logika* operator %(Logika& l);

        Logika* operator !();

};

ostream& operator <<(ostream& s, Logika& l);

#endif