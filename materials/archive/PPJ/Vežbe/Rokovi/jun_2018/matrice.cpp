#include "matrice.hpp"
#include <string>

using namespace std;

extern void yyerror(string s);

Matrica::Matrica(vector<vector<int>> m){
    matrica = m;
}

vector<vector<int>> Matrica::getMatrica(){
    return this->matrica;
}

Matrica* Matrica::operator +(Matrica& m) const{

    // cout << matrica.size() << endl;
    // for(int i=0; i<matrica.size(); i++){
    //     for(int j=0; j<matrica[i].size(); j++){
    //         cout << matrica[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl << endl;

    // for(int i=0; i<m.matrica.size(); i++){
    //     for(int j=0; j<m.matrica[i].size(); j++){
    //         cout << m.matrica[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    if(matrica.size() != m.matrica.size()){
        yyerror("Dimenzije matrica se ne poklapaju (pootkord sabiranje prvi if)");
    }

    if(matrica[0].size() != m.matrica[0].size()){
        yyerror("Dimenzije matrica se ne poklapaju (pootkord sabiranje drugi if)");
    }

    vector<vector<int>> vek;

    for(int i=0; i<matrica.size(); i++){
        vector<int> vrsta;
        for(int j=0; j<matrica[i].size(); j++){
            vrsta.push_back(matrica[i][j] + m.matrica[i][j]);
        }
        vek.push_back(vrsta);
    }

    return new Matrica(vek);
}

Matrica* Matrica::operator %(Matrica& m) const{ // pokoord mnozenje
    if(matrica.size() != m.matrica.size()){
        yyerror("Dimenzije matrica se ne poklapaju (pootkord mnozenje prvi if)");
    }

    if(matrica[0].size() != m.matrica[0].size()){
        yyerror("Dimenzije matrica se ne poklapaju (pootkord mnozenje drugi if)");
    }
    
    vector<vector<int>> vek;

    for(int i=0; i<matrica.size(); i++){
        vector<int> vrsta;
        for(int j=0; j<matrica[i].size(); j++){
            vrsta.push_back(matrica[i][j] * m.matrica[i][j]);
        }
        vek.push_back(vrsta);
    }

    return new Matrica(vek);
}
Matrica* Matrica::operator *(Matrica& m) const{ // matricno mnozenje
    if(matrica[0].size() != m.matrica.size()){
        yyerror("Ne mogu se mnoziti matrice koje nisu oblika NxM -> MxK ");
    }

    vector<vector<int>> nova;
    
    unsigned N = matrica.size();
    unsigned M = m.matrica[0].size();
    
    for(unsigned l = 0; l < matrica.size(); l++){
        vector<int> pom;
        for(unsigned i = 0; i < M; i++){
            int prom = 0;
            for(unsigned j = 0; j < N; j++)
                prom += matrica[l][j] * m.matrica[j][i];
            pom.push_back(prom);
        }
        nova.push_back(pom);
    }
    
    return new Matrica(nova);
}

Matrica* Matrica::transp() { // transponovanje
    vector<vector<int>> vek;

    int m = matrica[0].size();
    int n = matrica.size();

    for(int i=0; i<m; i++){
        vector<int> vrsta;
        for(int j=0; j<n; j++){
            vrsta.push_back(matrica[j][i]);
        }
        vek.push_back(vrsta);
    }

    return new Matrica(vek);
}

void Matrica::dodaj_vrstu(vector<int> vrsta){
    return matrica.push_back(vrsta);
}

void Matrica::show(ostream& s) const{
    s << "[";

    for(int i=0; i<matrica.size(); i++){
        s << "[";
        for(int j=0; j<matrica[i].size(); j++){
            if(j != 0)
                s << ", ";
            s << matrica[i][j];
        }
        s << "]";
        if(i != matrica.size()-1)
            s << ", ";
    }

    s << "]";
}

void Matrica::size(){
    cout << matrica.size() << "x" << matrica[0].size() << endl;
}

ostream& operator <<(ostream& s, Matrica& m){
    m.show(s);
    return s;
}