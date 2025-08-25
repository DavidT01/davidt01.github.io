#include "niska.hpp"

using namespace std;

extern void yyerror(string s);

Niska::Niska(string& s){
    niska = s;
}

Niska::Niska(int v){
    niska = to_string(v);
}

Niska::Niska(Niska& n){
    niska = n.niska;
}

void Niska::show(ostream& s){
    bool ind = true;
    for(int i=0; i<niska.size(); i++){
        if(!isdigit(niska[i])){
            ind = false;
            break;
        }
    }

    if(ind){
        s << stoi(niska, nullptr, 10);
    }else{
        for(int i=1; i<niska.size()-1; i++){
            s << niska[i];
        }
    }
}

Niska* Niska::operator +(Niska& s){
    int op1 = stoi(niska, nullptr, 10);
    int op2 = stoi(s.niska, nullptr, 10);

    int sabiranje = op1+op2;

    Niska* rez = new Niska(sabiranje);
    return rez;
}

Niska* Niska::operator -(Niska& s){
    int op1 = stoi(niska, nullptr, 10);
    int op2 = stoi(s.niska, nullptr, 10);

    int sabiranje = op1-op2;

    Niska* rez = new Niska(sabiranje);
    return rez;
}

Niska* Niska::operator *(Niska& s){
    int op1 = stoi(niska, nullptr, 10);
    int op2 = stoi(s.niska, nullptr, 10);

    int sabiranje = op1*op2;

    Niska* rez = new Niska(sabiranje);
    return rez;
}

Niska* Niska::operator /(Niska& s){
    int op1 = stoi(niska, nullptr, 10);
    int op2 = stoi(s.niska, nullptr, 10);

    int sabiranje = op1/op2;

    Niska* rez = new Niska(sabiranje);
    return rez;
}

Niska* Niska::operator -(){
    int op1 = stoi(niska, nullptr, 10);

    Niska* rez = new Niska(-op1);
    return rez;
}

Niska* Niska::concat(Niska& s){
    Niska* newStr = new Niska();
    newStr->niska = "\"";

    for(int i=1; i<niska.size()-1; i++){
        newStr->niska += niska[i];
    }

    for(int i=2; i<s.niska.size()-2; i++){
        newStr->niska += s.niska[i];
    }

    newStr->niska += '"';

    return newStr;
}

Niska* Niska::repeat(int v){
    Niska* newStr = new Niska();
    newStr->niska = "\"";

    for(int i=0; i<niska.size()-1; i++){
        newStr->niska += niska[i];
    }

    for(int i=1; i<v; i++){
        for(int j=1; j<niska.size()-1; j++){
            newStr->niska += niska[j];
        }
    }

    newStr->niska += niska[niska.size()-1];
    newStr->niska += '"';
    return newStr;
}

Niska* Niska::substring(int a, int b){
    if(a > b){
        yyerror("prvi arg ne moze biti veci od drugog");
    }

    Niska* newStr = new Niska();
    string ss = "";
    for(int i=1; i<niska.size()-1; i++){
        ss += niska[i];
    }

    cout << "NISKA " <<  ss << endl;

    newStr->niska = "\"";

    for(int i=a; i<b; i++){
        newStr->niska += ss[i];
    }

    newStr->niska += niska[niska.size()-1];
    newStr->niska += '"';
    return newStr;
}

ostream& operator <<(ostream& s, Niska& n){
    n.show(s);
    return s;
}