// https://arena.petlja.org/competition/asp-rokovi-1#tab_135201

#include <iostream>
#include <vector>

using namespace std;

const int N = 1e6;

int main() {

    vector<int> brojProizvoda(N);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int cena; cin >> cena;
        brojProizvoda[cena]++;
    }

    vector<int> ps(N + 1);
    for (int i = 0; i < N; i++)
        ps[i + 1] = ps[i] + brojProizvoda[i];

    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        cout << ps[b + 1] - ps[a] << endl;
    }

    return 0;

}