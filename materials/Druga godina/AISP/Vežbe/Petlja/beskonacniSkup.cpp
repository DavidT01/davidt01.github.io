#include <iostream>
#include <queue>

using namespace std;

//https://arena.petlja.org/sr-Latn-RS/competition/asp2021-domaci-2#tab_134057

//Pošto nam treba k najmanjih elemenata možemo koristiti red sa prioritetom
//Ako bismo samo deklarisali red sa prioritetom(npr. priority_queue<int> skup)
//on bi podrazumevano na svom vrhu uvek čuvao najveći element, a svi ostali bi redom bili manji
//dok je na dnu najmanji element i tada će nam funkcija skup.top() vratiti najveći element
//Da bismo napravili red sa obrnutim prioritetom koristimo:
//                         priority_queue<int, vector<int>, greater<int>> skup
//Sve što je sada potrebno jeste da ubacujemo redom elemente skupa i u svakom koraku ispišemo najmanji,
//dok ne ispišemo k elemenata
//Brojevi 2*n i 4*n-3 uvek su veći od n pa je prvi broj koji ispisujemo svakako n, a zatim dodajemo 2*n i 4*n-3 u red
//Sada u svakoj iteraciji izvučemo minimalni element reda i ispisujemo ga, a zatim od njega računamo 2*min i 4*min-3
//Složenost - operacije pop i push su reda O(logn), dok je top reda O(1), pa je ukupna složenost O(nlogn)

int main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<int, vector<int>, greater<int>> skup;
    skup.push(2 * n);
    skup.push(4 * n - 3);
    cout << n << " ";
    int i = 1;
    while (i < k)
    {
        int minEl = skup.top();
        cout << minEl << " ";
        skup.pop();
        skup.push(minEl * 2);
        skup.push(minEl * 4 - 3);
        i++;
    }
    return 0;
}