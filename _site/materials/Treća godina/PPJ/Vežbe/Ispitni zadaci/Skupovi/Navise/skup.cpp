#include "skup.hpp"

using namespace std;

Skup::Skup(int begin, int end) {
    for(int i = begin; i <= end; i++)
        elementi.insert(i);
}

Skup::Skup(set<int>& elementi) {
    this->elementi = elementi;
}

Skup::Skup(const Skup& s) {
    elementi = s.elementi;
}

void Skup::show(ostream& s) const {
    s << '{';
    for(auto it = elementi.begin(); it != elementi.end(); it++) {
        if(it != elementi.begin())
            s << ", ";
        s << *it;
    }
    s << '}';
}

Skup* Skup::operator +(Skup& s) const {
    Skup* newSet = new Skup(s);
    for(auto it = elementi.begin(); it != elementi.end(); it++)
        newSet->insert(*it);
    return newSet;
}

Skup* Skup::operator -(Skup& s) const {
    Skup* newSet = new Skup();
    for(auto it = elementi.begin(); it != elementi.end(); it++)
        if(!s.find(*it))
            newSet->insert(*it);
    return newSet;
}

Skup* Skup::operator *(Skup& s) const {
    Skup* newSet = new Skup();
    for(auto it = elementi.begin(); it != elementi.end(); it++)
        if(s.find(*it))
            newSet->insert(*it);
    return newSet;
}

bool Skup::find(int x) const {
    return elementi.find(x) != elementi.end();
}

bool Skup::subset(Skup& s) const {
    for(auto it = s.elementi.begin(); it != s.elementi.end(); it++)
        if(!this->find(*it))
            return false;
    return true;
}

int Skup::card(void) const {
    return elementi.size();
}

void Skup::insert(int x) {
    elementi.insert(x);
}

Skup* Skup::komplement(Skup& s) const {
    Skup* newSet = new Skup();
    for(auto it = elementi.begin(); it != elementi.end(); it++)
        if(!s.find(*it))
            newSet->insert(*it);
    return newSet;
}

ostream& operator <<(ostream& s, const Skup& set) {
    set.show(s);
    return s;
}