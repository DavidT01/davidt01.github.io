#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Matrica{
    private:
        vector<vector<int>> matrica;
    
    public:
        Matrica(){};
        Matrica(vector<vector<int>> m);

        vector<vector<int>> getMatrica();
        void size();

        Matrica* operator +(Matrica& m) const; // pokoord sabiranje
        Matrica* operator %(Matrica& m) const; // pokoord mnozenje
        Matrica* operator *(Matrica& m) const; // matricno mnozenje
        Matrica* transp();

        void dodaj_vrstu(vector<int> vrsta);

        void show(ostream& s) const;
};

ostream& operator <<(ostream& s, Matrica& m);

#endif