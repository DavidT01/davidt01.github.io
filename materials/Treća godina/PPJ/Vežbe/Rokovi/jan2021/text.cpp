#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main(){
    vector<tuple<int, int, int>> uglovi;
    
    uglovi.push_back({10, 10, 10});
    uglovi.push_back({10, 10, 10});
    uglovi.push_back({61, 1, 0});

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

        cout << "<" << noviSt << ", " << noviMin << ", " << noviSek << ">" << endl;
    }

    return 0;
}