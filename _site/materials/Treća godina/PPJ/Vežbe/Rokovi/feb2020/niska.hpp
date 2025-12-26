#ifndef NISKA_HPP
#define NISKA_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class Niska{
    private:
        string niska;
    public:
        Niska(){};
        Niska(string& s);
        Niska(int v);
        Niska(Niska& n);

        void show(ostream& s);

        Niska* operator +(Niska& s);
        Niska* operator -(Niska& s);
        Niska* operator *(Niska& s);
        Niska* operator /(Niska& s);
        Niska* operator -();

        Niska* concat(Niska& s);
        Niska* repeat(int v);
        Niska* substring(int a, int b);
};

ostream& operator <<(ostream& s, Niska& n);

#endif