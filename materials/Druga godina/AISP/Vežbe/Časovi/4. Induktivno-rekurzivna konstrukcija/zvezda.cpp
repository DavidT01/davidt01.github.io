// Особа је звезда (енгл. superstar) у некој групи људи ако њу сви остали познају, а она не познаје никога.
// Написати програм који одређује да ли у датој групи људи постоји звезда и која је то особа. Иако је за
// учитавање података потребно време које квадратно зависи од броја присутних особа, алгоритам треба да
// ради у времену које линеарно зависи од броја особа

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    vector<vector<int>> poznaje(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> poznaje[i][j];

    int mozdaZvezda = 0;
    for(int i = 1; i < n; i++)
        if(poznaje[mozdaZvezda][i])
            mozdaZvezda = i;

    bool zvezda = true;
    for(int i = 0; i < n; i++) {
        if(i != mozdaZvezda && !poznaje[i][mozdaZvezda])
            zvezda = false;
        if(i != mozdaZvezda && poznaje[mozdaZvezda][i])
            zvezda = false;
    }

    if(zvezda)
        cout << mozdaZvezda << endl;
    else
        cout << "Nema zvezde" << endl;
    return 0;
}