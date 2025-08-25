#include "matrix.hpp"

using namespace std;

Matrix::Matrix(int m, int n) {
    mx.resize(m);
    for(int i = 0; i < m; i++)
        mx[i].resize(n);
}

Matrix::Matrix(Matrix& m) {
    mx = m.mx;
}

bool Matrix::addRow(vector<double>& v) {
    if((mx.size() > 0) && (mx[0].size() != v.size()))
        return false;
    mx.push_back(v);
    return true;
}

void Matrix::show(ostream& s) const {
    for(int i = 0; i < mx.size(); i++) {
        for(int j = 0; j < mx[i].size(); j++)
            s << mx[i][j] << " ";
        s << endl;
    }
}

Matrix* Matrix::operator +(Matrix& m) const {
    if((mx.size() != m.mx.size()) || (mx[0].size() != m.mx[0].size()))
        return NULL;
    Matrix* newMatrix = new Matrix(mx.size(), mx[0].size());
    for(int i = 0; i < mx.size(); i++)
        for(int j = 0; j < mx[0].size(); j++)
            (*newMatrix)[i][j] = mx[i][j] + m.mx[i][j];
    return newMatrix;
}

Matrix* Matrix::operator -(Matrix& m) const {
    if((mx.size() != m.mx.size()) || (mx[0].size() != m.mx[0].size()))
        return NULL;
    Matrix* newMatrix = new Matrix(mx.size(), mx[0].size());
    for(int i = 0; i < mx.size(); i++)
        for(int j = 0; j < mx[0].size(); j++)
            (*newMatrix)[i][j] = mx[i][j] - m.mx[i][j];
    return newMatrix;
}

Matrix* Matrix::operator *(Matrix& m) const {
    if(mx[0].size() != m.mx.size())
        return NULL;
    Matrix* newMatrix = new Matrix(mx.size(), m.mx[0].size());
    for(int i = 0; i < mx.size(); i++)
        for(int j = 0; j < m.mx[0].size(); j++) {
            (*newMatrix)[i][j] = 0;
            for(int k = 0; k < mx[0].size(); k++)
                (*newMatrix)[i][j] += (mx[i][k] * m.mx[k][j]);
        }
    return newMatrix;
}

Matrix* Matrix::operator -() const {
    Matrix* newMatrix = new Matrix(mx.size(), mx[0].size());
    for(int i = 0; i < mx.size(); i++)
        for(int j = 0; j < mx[0].size(); j++)
            (*newMatrix)[i][j] = -mx[i][j];
    return newMatrix;
}

Matrix* Matrix::transpose() const {
    Matrix* newMatrix = new Matrix(mx[0].size(), mx.size());
    for(int i = 0; i < mx.size(); i++)
        for(int j = 0; j < mx[0].size(); j++)
            (*newMatrix)[j][i] = -mx[i][j];
    return newMatrix;
}

Matrix* Matrix::scalarMultiply(Matrix& m) const {
    if((mx.size() != m.mx.size()) || (mx[0].size() != m.mx[0].size()))
        return NULL;
    Matrix* newMatrix = new Matrix(mx.size(), mx[0].size());
    for(int i = 0; i < mx.size(); i++) {
        for(int j = 0; j < mx[0].size(); j++)
            (*newMatrix)[i][j] = mx[i][j] * m.mx[i][j];
    }
    return newMatrix;
}

vector<double> Matrix::operator [](int i) const {
    return mx[i];
}

vector<double>& Matrix::operator [](int i) {
    return mx[i];
}

ostream& operator <<(ostream& s, const Matrix& m) {
    m.show(s);
    return s;
}