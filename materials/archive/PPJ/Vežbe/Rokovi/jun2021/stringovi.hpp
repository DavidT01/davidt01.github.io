#ifndef STRINGOVI_HPP
#define STRINGOVI_HPP

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Stringovi{
    private:
        string niska;
    public:
        Stringovi(){};
        Stringovi(string& s);
        Stringovi(Stringovi& str);

        void show(ostream& s);

        Stringovi* operator +(Stringovi& str);
        Stringovi* operator *(int v);

        int size();
        int index(Stringovi& str);

        Stringovi* toLower();
        Stringovi* toUpper();
        Stringovi* reverse();

        Stringovi* fromAtoB(int a, int b);
        Stringovi* fromAtoEnd(int a);
        Stringovi* fromBeginToA(int a);
};

ostream& operator <<(ostream& s, Stringovi& str);

#endif