#include <iostream>

using namespace std;

//https://arena.petlja.org/competition/asp2021-poboljsanje-slozenosti#tab_132053

//Složenost - O(b - a)

int main()
{
    uint64_t a, b, c;
    cin >> a >> b >> c;
    if (a < b) //Namestimo da važi a >= b
        swap(a, b);
    if (a - b >= c) //Ako razliku između a i b ne možemo nadomestiti pomoću c onda sve dodajemo na manji broj
        b += c;
    else
    {
        while (b < a) //U suprotnom izjednačimo a i b
        {
            b++;
            c--;
        }
        //Ono što nam ostane podelimo ravnomerno između a i b
        if(c % 2) //Slučaj kada je c neparno
        {
            a += c / 2 + 1;
            b += c / 2;
        }
        else //Slučaj kada je c parno
        {
            a += c / 2;
            b += c / 2;
        }
    }
    //Nakon ažuriranja dužine i širine ispisujemo dobijenu površinu
    cout << a * b << endl;
    return 0;
}