#include <iostream>
#include <vector>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_132333

//Koristimo algoritam Eratostenovog sita kako bismo odredili koji broji manji ili jednaki n su prosti
//Zbir dva parna broja ili dva neparna broja je paran, a jedini prost paran broj je 2
//To znači da prost broj možemo dobiti samo kao zbir parnog i neparnog broja, pritom je 2 jedini paran prost broj
//Konačno, samo zbir broja 2 i nekog neparnog prostog broja može dati takođe prost broj
//Složenost - O(log(logn) + n) = O(n) 

int main() 
{
    long n;
    cin >> n;
    vector <bool> prosti(n + 1, true);
    prosti[0] = false;
    prosti[1] = false;
    for (int i = 2; i * i <= n; i++)
        if (prosti[i])
            for (int j = i * i; j <= n; j += i)
                prosti[j] = false;
    long brojac = 0;
    for (int q = 3; q + 2 < n; q++)
        if (prosti[q] && prosti[q + 2])
            brojac++;
    cout << brojac << endl;
    return 0;
}