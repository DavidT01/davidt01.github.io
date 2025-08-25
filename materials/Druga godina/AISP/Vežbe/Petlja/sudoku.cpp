#include <iostream>
#include <vector>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/resavanje_sudoku

const int n = 9;

bool provera(const vector<string>& s, int i, int j) {
    // da li se s[i][j] nalazi već u koloni j
    for (int k = 0; k < n * n; k++)
        if (k != i && s[i][j] == s[k][j])
            return true;
    // da li se s[i][j] nalazi već u vrsti i
    for (int k = 0; k < n * n; k++)
        if (k != j && s[i][j] == s[i][k])
            return true;
    // da li se s[i][j] već nalazi u kvadratu koji sadrži polje (i, j)
    int x = i / n, y = j / n;
    for (int k = x * n; k < (x + 1) * n; k++)
        for (int l = y * n; l < (y + 1) * n; l++)
            if ((k != i || l != j) && s[i][j] == s[k][l])
                return true;
    // ne postoji već ta vrednost
    return false;
}

bool sudoku(vector<string>& s, int pos)
{
    int i = pos / n, j = pos % n;
    if (pos == n * n)
        return true;
    if (s[i][j] != '0')
    return sudoku(s, pos + 1);
    for (char c = '1'; c <= '9'; c++)
    {
        s[i][j] = c;
        if (!provera(s, i, j))
            if (sudoku(s, pos + 1))
                return true;
    }
    s[i][j] = '0';
    return false;
}

int main()
{
    vector<string> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    if (sudoku(s, 0))
        for (int i = 0; i < n; i++)
            cout << s[i] << endl;
    return 0;
}