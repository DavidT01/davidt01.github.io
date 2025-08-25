#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Matrica{
    private:
        vector<vector<int>> matrica;
    public:
        Matrica(){};
        Matrica(Matrica& m);

        void size();
        void dodaj_vrstu(vector<int>& m);
        void show(ostream& s) const;

        // matricno mnozenje
        Matrica* operator *(Matrica& m);
        // pokoord sabiranje
        Matrica* operator +(Matrica& m);
        // pokoord mnozenje
        Matrica* operator %(Matrica& m);

        Matrica* transp();
};

ostream& operator <<(ostream& s, Matrica& m);

#endif