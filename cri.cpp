#include <fstream>
#define MAX_N 500
#define MAX_M 500
#define MAX_NR 8000
#define NR_ZONE 4
using namespace std;
ofstream scrie("cri.out");
struct Pereche { int x, y; };
struct Zona { Pereche coltStangaSus, coltDreaptaJos; };
Zona Z[NR_ZONE];
int N, M, X, Y, C[MAX_N+1][MAX_M+1];
void citesteDateleDeIntrare();
void initializeazaVectorulDeZone();
void calculeazaSolutieInZona(int, Pereche &);
void afiseazaSolutiaOptima(Pereche*);
int main()
{
	citesteDateleDeIntrare();
	initializeazaVectorulDeZone();
	Pereche solutie[NR_ZONE];
	for (int i = 0; i < NR_ZONE; i++)
		calculeazaSolutieInZona(i, solutie[i]);
	afiseazaSolutiaOptima(solutie);
	return 0;
}
void afiseazaSolutiaOptima(Pereche solutie[])
{
	int zona = 1;
	int nrGraunte = solutie[0].x;
	int nrCamere = solutie[0].y;
	for (int i = 1; i < NR_ZONE; i++)
		if (solutie[i].x > nrGraunte
		    || (solutie[i].x == nrGraunte
		        && solutie[i].y < nrCamere))
		{
			zona = i+1;
			nrGraunte = solutie[i].x;
			nrCamere = solutie[i].y;
		}
	ofstream scrie("cri.out");
	scrie << zona << ' ' << nrGraunte << ' ' << nrCamere;
	scrie.close();
}
bool esteNumarPar(int x)
{
	return x % 2 == 0;
}
bool potEvitaCamera(int nrLinie, int nrColoana, int nrZona)
{
	if (nrZona == 1 || nrZona == 2)
		if ((esteNumarPar(nrLinie) && esteNumarPar(nrColoana))
		    || (!esteNumarPar(nrLinie) && !esteNumarPar(nrColoana)))
			return 1;
	if (nrZona == 0 || nrZona == 3)
		if ((!esteNumarPar(nrLinie) && esteNumarPar(nrColoana))
		    || (esteNumarPar(nrLinie) && !esteNumarPar(nrColoana)))
			return 1;
	return 0;
}
void calculeazaSolutieInZona(int nrZona, Pereche & solutie)
{
	int primaLinie = Z[nrZona].coltStangaSus.x;
	int ultimaLinie= Z[nrZona].coltDreaptaJos.x;
	int primaColoana = Z[nrZona].coltStangaSus.y;
	int ultimaColoana = Z[nrZona].coltDreaptaJos.y;
	int nrLinii = ultimaLinie-primaLinie+1;
	int nrColoane = ultimaColoana-primaColoana+1;
	int minim = MAX_NR;
	int nrGraunte = 0;
	int nrCamere = nrLinii * nrColoane;
	bool cazSpecial = esteNumarPar(nrLinii) && esteNumarPar(nrColoane);
	for (int i = primaLinie; i <= ultimaLinie; i++)
		for (int j = primaColoana; j <= ultimaColoana; j++)
		{
			nrGraunte += C[i][j];
			if (cazSpecial
			    && potEvitaCamera(i, j, nrZona)
			    && C[i][j] < minim)
				minim = C[i][j];
		}
	if (cazSpecial)
	{
		nrGraunte -= minim;
		nrCamere--;
	}
	solutie.x = nrGraunte;
	solutie.y = nrCamere;
}
void initializeazaVectorulDeZone()
{
	Pereche coltStangaSusZona[] = {
		{1, 1},
		{1, Y},
		{X, 1},
		{X, Y}
	};
	Pereche coltDreaptaJosZona[] = {
		{X, Y},
		{X, M},
		{N, Y},
		{N, M}
	};
	for (int i = 0; i < NR_ZONE; i++)
	{
		Z[i].coltStangaSus = coltStangaSusZona[i];
		Z[i].coltDreaptaJos = coltDreaptaJosZona[i];
	}
}
void citesteDateleDeIntrare()
{
	ifstream citeste("cri.in");
	citeste >> N >> M >> X >> Y;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			citeste >> C[i][j];
	citeste.close();
}
