#include "matrice.hpp"

using namespace std;

extern void yyerror(string s);

Matrica::Matrica(Matrica& m){
    matrica = m.matrica;
}

void Matrica::dodaj_vrstu(vector<int>& m){
    matrica.push_back(m);
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

// matricno mnozenje
Matrica* Matrica::operator *(Matrica& m){
    if(matrica[0].size() != m.matrica.size()){
        yyerror("Ne mogu se mnoziti matrice koje nisu NxM <=> MxK formata");
    }

    Matrica* rez = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> tmp;
        for(int j=0; j<m.matrica[0].size(); j++){
            int val = 0;
            for(int k=0; k<matrica[0].size(); k++){
                val += matrica[i][k] * m.matrica[k][j];
            }
            tmp.push_back(val);
        }
        rez->dodaj_vrstu(tmp);
        tmp.clear();
    }

    return rez;
}

// A = [[1, 2]; [3, 4]]
// B = [[1, 1]; [0, 0]]

// A .+ B = [ [2, 3]; [3, 4] ]

// pokoord sabiranje
Matrica* Matrica::operator +(Matrica& m){
    if(matrica.size() != m.matrica.size()){
        yyerror("Matrice koje nisu iste velicine se ne mogu sabirati(pokoord)");
    }
    
    Matrica* rez = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> tmp;
        for(int j=0; j<matrica[0].size(); j++){
            tmp.push_back(matrica[i][j] + m.matrica[i][j]);
        }
        rez->dodaj_vrstu(tmp);
    }

    return rez;
}

// pokoord mnozenje
Matrica* Matrica::operator %(Matrica& m){
    if(matrica.size() != m.matrica.size()){
        yyerror("Matrice koje nisu iste velicine se ne mogu proizvod(pokoord)");
    }
    
    Matrica* rez = new Matrica();

    for(int i=0; i<matrica.size(); i++){
        vector<int> tmp;
        for(int j=0; j<matrica[0].size(); j++){
            tmp.push_back(matrica[i][j] * m.matrica[i][j]);
        }
        rez->dodaj_vrstu(tmp);
    }

    return rez;
}

Matrica* Matrica::transp(){
    Matrica* rez = new Matrica();

    for(int i=0; i<matrica[0].size(); i++){
        vector<int> tmp;
        for(int j=0; j<matrica.size(); j++){
            tmp.push_back(matrica[j][i]);
        }
        rez->dodaj_vrstu(tmp);
    }

    return rez;
}

ostream& operator <<(ostream& s, Matrica& m){
    m.show(s);
    return s;
}