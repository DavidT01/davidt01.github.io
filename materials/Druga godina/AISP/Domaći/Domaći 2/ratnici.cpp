#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Ratnik {
    uint32_t pozicija;
    uint32_t snaga;
    char smer;
};

bool poredi(Ratnik t1, Ratnik t2) {
    if(t1.pozicija >= t2.pozicija)
        return false;
    if(t2.pozicija > t1.pozicija)
        return true;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<Ratnik> ratnici(n);
    vector<uint32_t> org(n);
    for(int i = 0; i < n; i++) {
        cin >> ratnici[i].pozicija;
        org[i] = ratnici[i].pozicija;
    }
    for(int i = 0; i < n; i++)
        cin >> ratnici[i].snaga;
    for(int i = 0; i < n; i++)
        cin >> ratnici[i].smer;
    sort(ratnici.begin(), ratnici.end(), poredi);
    int i = 0, j = 1;
    while(ratnici[i].smer == 'L') {i++; j++;}
    while(i >= 0 && j < n) {
        if(ratnici[i].smer == 'D' && ratnici[j].smer == 'L') {
            if(ratnici[i].snaga > ratnici[j].snaga) {
                ratnici[i].snaga--;
                ratnici[j].snaga = 0;
                while(j < n && ratnici[j].snaga == 0) j++;
            }
            else if(ratnici[i].snaga < ratnici[j].snaga) {
                ratnici[i].snaga = 0;
                ratnici[j].snaga--;
                while(i >= 0 && ratnici[i].snaga == 0) i--;
                if(i < 0) {
                    i = j;
                    j = i + 1;
                    while(j < n && ratnici[j].snaga == 0) j++;
                }
            }
            else {
                ratnici[i].snaga = 0;
                ratnici[j].snaga = 0;
                while(j < n && ratnici[j].snaga == 0) j++;
                while(i >= 0 && ratnici[i].snaga == 0) i--;
                if(i < 0) {
                    i = j;
                    j = i + 1;
                    while(j < n && ratnici[j].snaga == 0) j++;
                }
            }
        }
        else {
            i = j;
            j = i + 1;
        }
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(ratnici[j].pozicija == org[i] && ratnici[j].snaga != 0) cout << ratnici[j].snaga << ' ';
    cout << endl;
    return 0;
}