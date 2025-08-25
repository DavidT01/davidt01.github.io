#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    char op;
    int raspon = 0;
    set<int> skup;
    while(n--)
    {
        cin >> op;
        if(op == 't')
        {
            int x;
            cin >> x;
            skup.insert(x);
        }
        else if(op == 'i')
        {
            int a, b;
            cin >> a >> b;
            if(skup.empty())
                cout << "0" << endl;
            else
            {
                auto pocetakS = skup.lower_bound(a);
                auto krajS = skup.lower_bound(b);
                if(pocetakS == skup.end())
                   raspon = 0;
                if(krajS != skup.begin() && (krajS == skup.end() || (b != *krajS)))
                    krajS--;
                if(*krajS <= *pocetakS || pocetakS == skup.end())
                    raspon = 0;
                else
                    raspon = *krajS - *pocetakS;
                cout << raspon << endl;
            }
        }
    }
    return 0;
}