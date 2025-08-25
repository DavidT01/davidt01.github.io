#ifndef LOGIKA_HPP
#define LOGIKA_HPP

#include <iostream>
#include <vector>

using namespace std;

class Logika{
    private:
        vector<int> vrednosti; // 0 false, 1 true, 2 undef
    
    public:
        Logika(){};
        Logika(Logika& l);
        Logika(int v);

        int operator[] (int i);
        int size();

        void dodaj_vrednost(int v);
        void show(ostream& s);

        // CONJ
        Logika* operator +(Logika& l);

        // DISJ
        Logika* operator -(Logika& l);

        // IMPL
        Logika* operator !=(Logika& l);

        // EQ
        Logika* operator ==(Logika& l);
        Logika* operator !();
};

ostream& operator <<(ostream& s, Logika& l);

#endif