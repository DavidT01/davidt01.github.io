// https://petlja.org/biblioteka/r/Zbirka2/resavanje_sudoku

#include <iostream>
#include <vector>

using namespace std;

const int n = 9;

bool provera(vector<string>& s, char c, int i, int j) {
    for(int k = 0; k < n; k++) {
        if(k != j && s[i][k] == c)
            return false;
        if(k != i && s[k][j] == c)
            return false;
    }
    return true;
}

bool sudoku(vector<string>& s, int pos) {
    int i = pos / n, j = pos % n;

    if(pos == n * n)
        return true;

    if(s[i][j] != '0')
        return sudoku(s, pos + 1);
    
    for(char c = '1'; c <= '9'; c++) {
        s[i][j] = c;
        if(provera(s, c, i, j) && sudoku(s, pos + 1))
            return true;
    }
    s[i][j] = '0';
    return false;
}

int main() {
    vector<string> s(n);
    for(int i = 0; i < n; i++)
        cin >> s[i];
    if(sudoku(s, 0))
        for(int i = 0; i < n; i++)
            cout << s[i] << endl;
    else
        cout << "Nije moguce resiti ovaj sudoku" << endl;
    return 0;
}