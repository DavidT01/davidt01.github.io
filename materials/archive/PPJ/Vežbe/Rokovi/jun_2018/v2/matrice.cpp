#include "matrice.hpp"

using namespace std;

extern void yyerror(string s);

Matrica::Matrica(vector<vector<int>>& m){
    matrica = m;
}

Matrica::Matrica(Matrica& m){
    matrica = m.matrica;
}

void Matrica::size(){
    cout << matrica.size() << "x" << matrica[0].size() << endl;
}

void Matrica::show(ostream& s) const{
    s << "[";

    for(int i=0; i<matrica.size(); i++){
        s << "[";
        for(int j=0; j<matrica[i].size(); j++){
            s << matrica[i][j] << ", ";
        }
        s << "];";
    }

    s << "]";
}

void Matrica::dodaj_vrstu(vector<int>& m){
    matrica.push_back(m);
}

vector<vector<int>> Matrica::getMatrica(){
    return matrica;
}

Matrica* Matrica::operator +(Matrica& m) const{ // pokoord sabiranje
    if(matrica.size() != m.matrica.size()){
        yyerror("Matrice nisu istih velicina (pokoord sabiranje)");
    }

    for(int i=0; i<matrica.size(); i++){
        if(matrica[i].size() != m.matrica[i].size())
            yyerror("Matrice nisu istih velicina (pokoord sabiranje)");
    }

    Matrica* novaMat = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> vrsta;
        for(int j=0; j<matrica[i].size(); j++){
            vrsta.push_back(matrica[i][j] + m.matrica[i][j]);
        }
        novaMat->matrica.push_back(vrsta);
    }

    return novaMat;
}

Matrica* Matrica::operator %(Matrica& m) const{ // pokoord mnozenje
    if(matrica.size() != m.matrica.size()){
        yyerror("Matrice nisu istih velicina (pokoord mnozenje)");
    }

    for(int i=0; i<matrica.size(); i++){
        if(matrica[i].size() != m.matrica[i].size())
            yyerror("Matrice nisu istih velicina (pokoord mnozenje)");
    }

    Matrica* novaMat = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> vrsta;
        for(int j=0; j<matrica[i].size(); j++){
            vrsta.push_back(matrica[i][j] * m.matrica[i][j]);
        }
        novaMat->matrica.push_back(vrsta);
    }

    return novaMat;
}

Matrica* Matrica::operator *(Matrica& m) const{ // matricno mnozenje
    if(matrica[0].size() != m.matrica.size()){
        yyerror("Ne mogu se mnoziti matrice ako nisu oblika NxM i MxK");
    }

    Matrica* novaMat = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> pom;
        for(int j=0; j<m.matrica[i].size(); j++){
            int rez = 0;
            for(int k=0; k<matrica.size(); k++){
                rez += matrica[i][k] * m.matrica[k][j];
            }
            pom.push_back(rez);
        }
        novaMat->matrica.push_back(pom);
    }

    return novaMat;
}

Matrica* Matrica::transponovanje(){
    Matrica* novaMat = new Matrica();

    for(int i=0; i<matrica[0].size(); i++){
        vector<int> vrsta;
        for(int j=0; j<matrica.size(); j++){
            vrsta.push_back(matrica[j][i]);
        }
        novaMat->matrica.push_back(vrsta);
    }

    return novaMat;
}

ostream& operator <<(ostream& s, Matrica& m){
    m.show(s);
    return s;
}