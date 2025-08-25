#ifndef UGAO_HPP
#define UGAO_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>

using namespace std;

class Ugao{
    private:
        vector<tuple<int, int, int>> uglovi;
    
    public:
        Ugao(){};
        Ugao(Ugao& u);
        Ugao(int st, int min, int sek);

        void dodajUgao(int st, int min, int sek);

        int size();

        int getStepene();
        int getMinute();
        int getSekunde();

        int getStepene2(int v);
        int getMinute2(int v);
        int getSekunde2(int v);

        void show(ostream& s);

        Ugao* operator +(Ugao& u);
        Ugao* operator -(Ugao& u);
        Ugao* operator *(int v);

        Ugao* kom();
        Ugao* sup();
};

ostream& operator <<(ostream& s, Ugao& u);

#endif