#include <iostream>
#include <map>

using namespace std;

//Napisati funkcije dodaj, obrisi, vrednost, uvecaj i uvecajSve pomoću mape.

map<int, int> m;
int uvecanje = 0;

void dodaj(int x, int y)
{
    m[x] = y - uvecanje;
}

void obrisi(int x)
{
    m.erase(x);
}

int vrednost(int x)
{
    return m[x] + uvecanje;
}

void uvecaj(int x, int y)
{
    m[x] += y;
}

void uvecajSve(int y)
{
    uvecanje += y;
}

int main()
{
    
    return 0;
}