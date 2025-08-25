#ifndef BROJ_HPP
#define BROJ_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

class Broj{
    private:
        vector<int> brojevi;
    public:
        Broj(){};
        Broj(int v);
        Broj(Broj& v);

        void show();
        void show2(string& format);
        void dodaj_broj(int v);

        int operator [](int v);

        Broj* operator +(Broj& b);
        Broj* operator -(Broj& b);
        Broj* operator *(Broj& b);
        Broj* operator /(Broj& b);
        Broj* operator %(Broj& b);
        Broj* operator -();

        Broj* operator ^(Broj& b);
        Broj* operator &(Broj& b);
        Broj* operator |(Broj& b);
        Broj* operator >>(Broj& b);
        Broj* operator <<(Broj& b);
        Broj* operator ~();
};

#endif