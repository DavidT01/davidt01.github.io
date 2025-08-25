#include <iostream>

using namespace std;

//Definisati funkciju koja izračunava dijametar datog binarnog drveta
//Dijametar binarnog drveta je broj čvorova na najdužoj putanji između dva čvora u drvetu
//(računajući i te čvorove, ali samo jednom ako se poklapaju)

//Jasno je da će najduži put između dva čvora biti put između neka dva lista
//Ako dijametar ne sadrži koren drveta, on se nalazi ili u levom ili desno podstablu
//Ako dijametar sadrži koren drveta, to znači da je potrebno naći najduži put od korena do nekog lista
//levo i najduži put od korena do nekog lista desno, sabrati ih i na to dodati 1(koren)
//Najduži put levo i desno od korena su zapravo visine levog i desnog podstabla
//Na kraju, dijametar drveta će biti maksimum dijametra levog podstabla, dijametra desnog podstabla i
//zbira visine levog i desnog podstabla i 1(korena)
//Složenost - u isto vreme računamo i visinu i dijametar pa je složenost O(n)

struct Cvor
{
	int vrednost;
	Cvor* levo;
	Cvor* desno;
};

void dijametar_i_visina(Cvor* koren, int& dijametar, int& visina)
{
	if (koren == nullptr)
		return;
	int dl, dd, vl, vd;
	dijametar_i_visina(koren->levo, dl, vl);
	dijametar_i_visina(koren->desno, dd, vd);
	visina = max(vl, vd) + 1;
	dijametar = max({ dl, dd, vl + vd + 1 });
}

int dijametar(Cvor* koren)
{
	int d, v;
	dijametar_i_visina(koren, d, v);
	return d;
}

int main()
{
	Cvor* koren;
	//Učitamo stablo
	cout << dijametar(koren) << endl;
	//Obrišemo stablo
	return 0;
}