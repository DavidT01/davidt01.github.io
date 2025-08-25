#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Matrica{
    public:
        Matrica(){};
        Matrica(vector<vector<int>>& m);
        Matrica(Matrica& m);

        void show(ostream& s) const;

        void size();

        void dodaj_vrstu(vector<int>& m);
        vector<vector<int>> getMatrica();

        Matrica* operator +(Matrica& m) const; // pokoord sabiranje
        Matrica* operator %(Matrica& m) const; // pokoord mnozenje
        Matrica* operator *(Matrica& m) const; // matricno mnozenje

        Matrica* transponovanje();

    private:
        vector<vector<int>> matrica;
};

ostream& operator <<(ostream& s, Matrica& m);

#endif