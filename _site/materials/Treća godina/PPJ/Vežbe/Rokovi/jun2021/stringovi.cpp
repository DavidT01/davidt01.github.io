#include "stringovi.hpp"

using namespace std;

Stringovi::Stringovi(string& s){
    niska = s;
}

Stringovi::Stringovi(Stringovi& str){
    niska = str.niska;
}

void Stringovi::show(ostream& s){
    for(int i=1; i<niska.size()-1; i++){
        if(niska[i] == '\\' && niska[i+1] == 'n'){
            s << endl;
            i++;
        }else if(niska[i] == '\\' && niska[i+1] == 't'){
            s << "    ";
            i++;
        }
        else s << niska[i];
    }
}

Stringovi* Stringovi::operator +(Stringovi& str){
    Stringovi* newStr = new Stringovi();
    for(int i=0; i<niska.size()-1; i++){
        newStr->niska += niska[i];
    }

    for(int i=1; i<str.niska.size()-1; i++){
        newStr->niska += str.niska[i];
    }

    newStr->niska += niska[niska.size()-1];
    return newStr;
}

Stringovi* Stringovi::operator *(int v){
    Stringovi* newStr = new Stringovi();
    for(int i=0; i<niska.size()-1; i++){
        newStr->niska += niska[i];
    }

    for(int i=1; i<v; i++){
        for(int j=1; j<niska.size()-1; j++){
            newStr->niska += niska[j];
        }
    }

    newStr->niska += niska[niska.size()-1];
    return newStr;
}

int Stringovi::size(){
    return niska.size()-2;
}

int Stringovi::index(Stringovi& str){
    string s = "";
    for(int i=1; i<str.niska.size()-1; i++){
        s += str.niska[i];
    }

    auto pos = niska.find(s);
    return pos-1;
}

Stringovi* Stringovi::toLower(){
    Stringovi* newStr = new Stringovi();
    newStr->niska = "";

    for(int i=0; i<niska.size(); i++){
        newStr->niska += tolower(niska[i]);
    }

    return newStr;
}

Stringovi* Stringovi::toUpper(){
    Stringovi* newStr = new Stringovi();
    newStr->niska = "";

    for(int i=0; i<niska.size(); i++){
        newStr->niska += toupper(niska[i]);
    }

    return newStr;
}

Stringovi* Stringovi::reverse(){
    Stringovi* newStr = new Stringovi();
    newStr->niska = "";

    for(int i=niska.size()-1; i>=0; i--){
        newStr->niska += niska[i];
    }

    return newStr;
}

Stringovi* Stringovi::fromAtoB(int a, int b){
    Stringovi* newStr = new Stringovi();
    string ss = "";
    for(int i=1; i<niska.size()-1; i++){
        ss += niska[i];
    }

    newStr->niska = "\"";

    for(int i=a; i<b; i++){
        newStr->niska += ss[i];
    }

    newStr->niska += '"';
    return newStr;
}

Stringovi* Stringovi::fromAtoEnd(int a){
    Stringovi* newStr = new Stringovi();
    string ss = "";
    for(int i=1; i<niska.size()-1; i++){
        ss += niska[i];
    }

    newStr->niska = "\"";

    for(int i=a; i<ss.size(); i++){
        newStr->niska += ss[i];
    }

    newStr->niska += '"';
    return newStr;
}

Stringovi* Stringovi::fromBeginToA(int a){
    Stringovi* newStr = new Stringovi();
    string ss = "";
    for(int i=1; i<niska.size()-1; i++){
        ss += niska[i];
    }

    newStr->niska = "\"";

    for(int i=0; i<a; i++){
        newStr->niska += ss[i];
    }

    newStr->niska += '"';
    return newStr;
}

ostream& operator <<(ostream& s, Stringovi& str){
    str.show(s);
    return s;
}