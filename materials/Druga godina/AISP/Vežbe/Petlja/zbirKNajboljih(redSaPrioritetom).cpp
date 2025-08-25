#include <iostream>
#include <queue>

using namespace std;

//https://petlja.org/biblioteka/r/Zbirka2/zbir_k_najboljih1

int main()
{
    int n, k, x;
    cin >> n >> k;
    priority_queue<int, vector<int>, greater<int>> najvecihK; //Sada red sa prioritetom izbacuje najmanji element
    for (int i = 0; i < k; i++)
    {
        cin >> x;
            najvecihK.push(x);
    }
    for (int i = k; i < n; i++)
    {
        cin >> x;
        if (x > najvecihK.top())
        {
            najvecihK.pop();
            najvecihK.push(x);
        }
    }
    int zbir = 0;
    while (!najvecihK.empty())
    {
        zbir += najvecihK.top();
        najvecihK.pop();
    }
    cout << zbir << endl;
    return 0;
}