#include "broj.hpp"

using namespace std;

extern void yyerror(string s);

Broj::Broj(int v){
    brojevi.push_back(v);
}

Broj::Broj(Broj& v){
    brojevi = v.brojevi;
}

void Broj::show(){
    if(brojevi.size() > 1){
        printf("[");
        for(int i=0; i<brojevi.size(); i++){
            printf("%d, ", brojevi[i]);
        }
        printf("]\n");
    }else{
        printf("%d\n", brojevi[0]);
    }
}

void Broj::show2(string& format){
    string f = "";
    for(int i=1; i<format.size()-1; i++){
        f += format[i];
    }

    if(brojevi.size() > 1){
        printf("[");
        for(int i=0; i<brojevi.size(); i++){
            if(f == "%x"){
                printf("0x%x, ", brojevi[i]);
            }else if(f == "%b"){
                printf("%bb, ", brojevi[i]);
            }else if(f == "%o"){
                printf("0%o, ", brojevi[i]);
            }else{
                printf("%d, ", brojevi[i]);
            }
        }
        printf("]\n");
    }else{
        if(f == "%x"){
            printf("0x%x\n", brojevi[0]);
        }else if(f == "%b"){
            printf("%bb\n", brojevi[0]);
        }else if(f == "%o"){
            printf("0%o\n", brojevi[0]);
        }else{
            printf("%d\n", brojevi[0]);
        }
    }
    
}

void Broj::dodaj_broj(int v){
    brojevi.push_back(v);
}

int Broj::operator [](int v){
    return brojevi[v];
}

Broj* Broj::operator +(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se sabirati dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] + b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(brojevi[i] + b.brojevi[0]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(b.brojevi[i] + brojevi[0]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] + b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator -(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se oduzimati dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] - b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] - brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] - b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] - b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator *(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se mnoziti dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] * b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(brojevi[i] * b.brojevi[0]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(b.brojevi[i] * brojevi[0]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] * b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator /(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se deliti dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] / b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(brojevi[i] / b.brojevi[0]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(b.brojevi[i] / brojevi[0]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] / b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator %(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se oduzimati dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] % b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] % brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] % b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] % b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator -(){
    Broj* rez = new Broj();

    for(int i=0; i<brojevi.size(); i++){
        rez->dodaj_broj(-brojevi[i]);
    }

    return rez;
}

Broj* Broj::operator ^(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se ^ dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] ^ b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] ^ brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] ^ b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] ^ b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator &(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se & dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] & b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] & brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] & b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] & b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator |(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se | dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] | b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] | brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] | b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] | b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator >>(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se SHR dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] >> b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] >> brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] >> b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] >> b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator <<(Broj& b){
    Broj* rez = new Broj();

    int len1 = brojevi.size();
    int len2 = b.brojevi.size();

    if(len1 > 1 && len2 > 1){
        if(len1 != len2){
            yyerror("Ne mogu se SHL dve liste razlicitih duzina");
        }

        for(int i=0; i<len1; i++){
            rez->dodaj_broj(brojevi[i] << b.brojevi[i]);
        }
    }else{
        if(len1 > 1){
            for(int i=0; i<len1; i++){
                rez->dodaj_broj(b.brojevi[0] << brojevi[i]);
            }
        }else if(len2 > 1){
            for(int i=0; i<len2; i++){
                rez->dodaj_broj(brojevi[0] << b.brojevi[i]);
            }
        }else{
            rez->dodaj_broj(brojevi[0] << b.brojevi[0]);
        }
    }

    return rez;
}

Broj* Broj::operator ~(){
    Broj* rez = new Broj();

    for(int i=0; i<brojevi.size(); i++){
        rez->dodaj_broj(-brojevi[i]);
    }

    return rez;
}
