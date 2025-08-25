#include <iostream>
#include <stack>

using namespace std;

//Izračunati vrednost min-maks izraza.
//m - min dva broja, M - max dva broja
//pr. ((3m5)M(4m(2M6))) = 4

int main()
{
    string izraz;
    cin >> izraz;
    stack<char> operacije;
    stack<int> vrednosti;
    for (char c : izraz)
    {
        if (isdigit(c))
            vrednosti.push(c - '0');
        else if (c == 'm' || c == 'M')
            operacije.push(c);
        else if (c == ')')
        {
            int a = vrednosti.top();
            vrednosti.pop();
            int b = vrednosti.top();
            vrednosti.pop();
            char op = operacije.top();
            operacije.pop();
            int rez = op == 'm' ? min(a, b) : max(a, b);
            vrednosti.push(rez);
        }
    }
    cout << vrednosti.top() << endl;
    return 0;
}