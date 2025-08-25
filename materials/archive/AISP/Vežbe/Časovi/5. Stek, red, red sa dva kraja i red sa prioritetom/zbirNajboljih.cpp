// https://petlja.org/biblioteka/r/Zbirka2/zbir_k_najboljih1

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n, k, x; cin >> n >> k;
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 0; i < k; i++) {
        cin >> x;
        q.push(x);
    }

    for(int i = k; i < n; i++) {
        cin >> x;
        if(x > q.top()) {
            q.pop();
            q.push(x);
        }
    }

    int zbir = 0;
    while(!q.empty()) {
        zbir += q.top();
        q.pop();
    }
    cout << zbir << endl;
    return 0;
}