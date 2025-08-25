#include "vektor.hpp"

using namespace std;

Vektor::Vektor(double a, double b){
    x = a;
    y = b;
}

Vektor::Vektor(Vektor& v){
    x = v.x;
    y = v.y;
}

Vektor::Vektor(double x1, double y1, double x2, double y2){
    x = x2-x1;
    y = y2-y1;
}

void Vektor::show(ostream& s) const{
    s << "<" << x << ", " << y << ">";
}

Vektor* Vektor::operator +(Vektor& v){
    Vektor* rez = new Vektor();
    rez->x = x + v.x;
    rez->y = y + v.y;

    return rez;
}

Vektor* Vektor::operator -(Vektor& v){
    Vektor* rez = new Vektor();
    rez->x = x - v.x;
    rez->y = y - v.y;

    return rez;
}

Vektor* Vektor::operator -(){
    Vektor* rez = new Vektor(-x, -y);
    return rez;
}

Vektor* Vektor::operator *(double skalar){
    Vektor* rez = new Vektor(x*skalar, y*skalar);
    return rez;
}

Vektor* Vektor::sim(){
    Vektor* rez = new Vektor(-x, -y);
    return rez;
}

Vektor* Vektor::refx(){
    Vektor* rez = new Vektor(x, -y);
    return rez;
}

Vektor* Vektor::refy(){
    Vektor* rez = new Vektor(-x, y);
    return rez;
}

//  cos(fi)   -sin(fi)    = > x*cos(fi) - y*sin(fi)
//  sin(fi)   cos(fi)     = > x*sin(fi) + y*cos(fi)
//= cos^2 + sin^ = 1

Vektor* Vektor::rot(double angle){
    double newX = x*cos(angle) - y*sin(angle);
    double newY = x*sin(angle) + y*cos(angle);

    return new Vektor(newX, newY);
}

double Vektor::norm(){
    double rez = sqrt((x*x)+(y*y));
    return rez;
}

double Vektor::angle(Vektor& v1, Vektor& v2){
    double prodX = v1.x * v2.x;
    double prodY = v1.y * v2.y;

    double normV1 = sqrt((v1.x*v1.x)+(v1.y*v1.y));
    double normV2 = sqrt((v2.x*v2.x)+(v2.y*v2.y));

    double dotProduct = prodX + prodY;
    double norm = normV1*normV2;

    double angle = acos(dotProduct / norm);
    return angle * 180 / M_PI;
}

ostream& operator <<(ostream& s, Vektor& v){
    v.show(s);
    return s;
}