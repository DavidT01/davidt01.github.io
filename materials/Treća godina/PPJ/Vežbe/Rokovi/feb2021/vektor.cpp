#include "vektor.hpp"
#include <cmath>
#include <iostream>

using namespace std;

extern void yyerror();

Vektor::Vektor(double x1, double y1, double x2, double y2){
    x = x2-x1;
    y = y2-y1;
}

Vektor::Vektor(double a, double b){
    x = a;
    y = b;
}

Vektor::Vektor(Vektor* v){
    x = v->x;
    y = v->y;
}

void Vektor::show(ostream& s) const{
    s << "<" << this->x << ", " << this->y << ">";
}

Vektor* Vektor::operator +(Vektor& v) const{
    return new Vektor(this->x + v.x, this->y + v.y);
}

Vektor* Vektor::operator -(Vektor& v) const{
    return new Vektor(this->x - v.x, this->y - v.y);
}

Vektor* Vektor::operator *(double skalar) const{
    return new Vektor(this->x*skalar, this->y * skalar);
}

Vektor* Vektor::sim() const{
    return new Vektor(-this->x, -this->y);
}

Vektor* Vektor::refx() const{
    return new Vektor(this->x, -this->y);
}

Vektor* Vektor::refy() const{
    return new Vektor(-this->x, this->y);
}

Vektor* Vektor::rot(double theta) const{
    double new_x = cos(theta)*this->x - sin(theta)*this->y;
    double new_y = sin(theta)*this->x + cos(theta)*this->y;
    return new Vektor(new_x, new_y);
}

double Vektor::norm() const{
    return sqrt((this->x * this->x) + (this->y * this->y));
}

double Vektor::angle(const Vektor& a, const Vektor& b){
    double prod_x = a.x * b.x;
    double prod_y = a.y * b.y;

    double dotProduct = prod_x + prod_y;
    double normProduct = a.norm() * b.norm();
    
    double angle = acos(dotProduct / normProduct);

    return angle*180/M_PI;
}

ostream& operator <<(ostream& s, Vektor& vektor){
    vektor.show(s);
    return s;
}