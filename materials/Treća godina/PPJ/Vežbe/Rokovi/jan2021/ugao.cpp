#include "ugao.hpp"

using namespace std;

extern void yyerror(string s);

Ugao::Ugao(Ugao& u){
    uglovi = u.uglovi;
}

// <120, 50, 123> ----> <120, 52, 3>

Ugao::Ugao(int st, int min, int sek){
    int prenos;
    if(sek >= 60){
        prenos = sek / 60;
        sek %= 60;
        min += prenos;
    }

    if(min >= 60){
        prenos = min / 60;
        min %= 60;
        st += prenos;
    }

    if(st > 360){
        prenos = st / 360;
        st %= 360;
    }

    uglovi.push_back({st, min, sek});
}

int Ugao::size(){
    return uglovi.size();
}

void Ugao::dodajUgao(int st, int min, int sek){
    uglovi.push_back({st, min, sek});
}

int Ugao::getStepene(){
    return get<0>(uglovi[0]);
}

int Ugao::getMinute(){
    return get<1>(uglovi[0]);
}

int Ugao::getSekunde(){
    return get<2>(uglovi[0]);
}

int Ugao::getStepene2(int v){
    return get<0>(uglovi[v]);
}

int Ugao::getMinute2(int v){
    return get<1>(uglovi[v]);
}

int Ugao::getSekunde2(int v){
    return get<2>(uglovi[v]);
}

void Ugao::show(ostream& s){
    for(auto x : uglovi){
        s << "<" << get<0>(x) << ", " << get<1>(x) << ", " << get<2>(x) << ">, ";
    }
}

Ugao* Ugao::operator +(Ugao& u){
    int noviSt = getStepene() + u.getStepene();
    int noviMin = getMinute() + u.getMinute();
    int noviSek = getSekunde() + u.getSekunde();

    int prenos;
    if(noviSek >= 60){
        prenos = noviSek / 60;
        noviSek %= 60;
        noviMin += prenos;
    }

    if(noviMin >= 60){
        prenos = noviMin / 60;
        noviMin %= 60;
        noviSt += prenos;
    }

    if(noviSt > 360){
        prenos = noviSt / 360;
        noviSt %= 360;
    }

    return new Ugao(noviSt, noviMin, noviSek);
}

Ugao* Ugao::operator -(Ugao& u){
    int noviSt = getStepene() - u.getStepene();
    int noviMin = getMinute() - u.getMinute();
    int noviSek = getSekunde() - u.getSekunde();

    int prenos;
    if(noviSek >= 60){
        prenos = noviSek / 60;
        noviSek %= 60;
        noviMin += prenos;
    }

    if(noviMin >= 60){
        prenos = noviMin / 60;
        noviMin %= 60;
        noviSt += prenos;
    }

    if(noviSt > 360){
        prenos = noviSt / 360;
        noviSt %= 360;
    }

    return new Ugao(noviSt, noviMin, noviSek);
}

Ugao* Ugao::operator *(int v){
    int noviSt = getStepene() * v;
    int noviMin = getMinute() * v;
    int noviSek = getSekunde() * v;

    int prenos;
    if(noviSek >= 60){
        prenos = noviSek / 60;
        noviSek %= 60;
        noviMin += prenos;
    }

    if(noviMin >= 60){
        prenos = noviMin / 60;
        noviMin %= 60;
        noviSt += prenos;
    }

    if(noviSt > 360){
        prenos = noviSt / 360;
        noviSt %= 360;
    }

    return new Ugao(noviSt, noviMin, noviSek);
}

// <90, 0, 0> - ugao
Ugao* Ugao::kom(){
    Ugao* rez = new Ugao();
    
    for(int i=0; i<uglovi.size(); i++){
        int noviSt = 89 - get<0>(uglovi[i]);
        int noviMin = 59 - get<1>(uglovi[i]);
        int noviSek = 60 - get<2>(uglovi[i]);

        int prenos;
        if(noviSek >= 60){
            prenos = noviSek / 60;
            noviSek %= 60;
            noviMin += prenos;
        }

        if(noviMin >= 60){
            prenos = noviMin / 60;
            noviMin %= 60;
            noviSt += prenos;
        }

        if(noviSt > 360){
            prenos = noviSt / 360;
            noviSt %= 360;
        }

        rez->dodajUgao(noviSt, noviMin, noviSek);
    }

    return rez;
}

// <180, 0, 0> - ugao
Ugao* Ugao::sup(){
    int noviSt = 179 - getStepene();
    int noviMin = 59 - getMinute();
    int noviSek = 60 - getSekunde();

    int prenos;
    if(noviSek >= 60){
        prenos = noviSek / 60;
        noviSek %= 60;
        noviMin += prenos;
    }

    if(noviMin >= 60){
        prenos = noviMin / 60;
        noviMin %= 60;
        noviSt += prenos;
    }

    if(noviSt > 360){
        prenos = noviSt / 360;
        noviSt %= 360;
    }

    return new Ugao(noviSt, noviMin, noviSek);
}

ostream& operator <<(ostream& s, Ugao& u){
    u.show(s);
    return s;
}