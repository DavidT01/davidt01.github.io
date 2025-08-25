#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <vector>

using namespace std;

class Matrix {

    private:
        vector<vector<double>> mx;

    public:
        Matrix() {};
        Matrix(int m, int n);
        Matrix(Matrix& m);

        bool addRow(vector<double>& v);
        void show(ostream& s) const;

        Matrix* operator +(Matrix& m) const;
        Matrix* operator -(Matrix& m) const;
        Matrix* operator *(Matrix& m) const;
        Matrix* operator -() const;

        Matrix* transpose() const;
        Matrix* scalarMultiply(Matrix& m) const;

        vector<double> operator [](int i) const;
        vector<double>& operator [](int i);
};

ostream& operator <<(ostream& s, const Matrix& m);

#endif