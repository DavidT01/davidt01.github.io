// Мин-макс изрази се граде применом две инфиксно записане операције:
// • операција m означава проналажење минимума два броја;
// • операција M означава проналажење максимума два броја.
// Напиши програм који израчунава вредност датог израза у коме је свака примена операције ограђена заградама
// (дакле израз је или једна цифра или је облика (<izraz> op <izraz>)).


#include <iostream>
#include <stack>

using namespace std;

int main() {
    string izraz; cin >> izraz;
    stack<char> op;
    stack<int> vr;
    for(char c : izraz) {
        if(isdigit(c))
            vr.push(c - '0');
        else if(c == 'm' || c == 'M')
            op.push(c);
        else if(c == ')') {
            int a = vr.top(); vr.pop();
            int b = vr.top(); vr.pop();
            char opr = op.top(); op.pop();
            int rez = (opr == 'm' ? min(a, b) : max(a, b));
            vr.push(rez);
        }
    }
    cout << vr.top() << endl;
    return 0;
}