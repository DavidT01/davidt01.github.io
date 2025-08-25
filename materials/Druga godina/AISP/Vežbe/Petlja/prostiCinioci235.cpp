#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/prosti_cinioci_2351

int main()
{
    int n;
    cin >> n;
    queue<uint64_t> q2, q3, q5;
    uint64_t el = 1;
    q2.push(2);
    q3.push(3);
    q5.push(5);
    while (n--)
    {
        el = min({ q2.front(), q3.front(), q5.front() });
        q2.push(2 * el);
        q3.push(3 * el);
        q5.push(5 * el);
        if (q2.front() == el)
            q2.pop();
        if (q3.front() == el)
            q3.pop();
        if (q5.front() == el)
            q5.pop();
    }
    cout << el << endl;
    return 0;
}