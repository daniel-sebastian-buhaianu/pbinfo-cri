#include <fstream>
#include <iostream>
#define MAX_N 500
#define MAX_M 500
#define NR_ZONE 4
#define NR_DIRECTII 4
using namespace std;
struct Coordonate { int x, y; };
struct Zona { Coordonate dest, limx, limy; };
struct Camera { Coordonate poz; Camera *urm };
struct ListaCamere { Camera *inc, *sf; };
struct Solutie { int z, t, k; };
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int N, M, X, Y, C[MAX_N][MAX_M];
void citesteDateleDeIntrare();
void initializeazaVectorDeZone(Zona*);
void calculeazaTraseuOptimInZona(Zona, Solutie &);
void calculeazaRezultat(Solutie*, Solutie &);
int main()
{
	Solutie S[NR_ZONE], sol;
	Zona Z[NR_ZONE];
	citesteDateleDeIntrare();
	initializeazaVectorDeZone(Z);
	for (int i = 0; i < NR_ZONE; i++)
		calculeazaTraseuOptimInZona(Z[i], S[i]);
	calculeazaRezultat(S, sol);
	ofstream scrie("cri.out");
	//scrie << sol.z << ' ' << sol.t << ' ' << sol.k;
	scrie.close();
	return 0;
}
void calculeazaRezultat(Solutie S[], Solutie & sol)
{
	//TODO
}
void adaugaCameraInLista(ListaCamere & L, Coordonate poz)
{
	Camera *cam = new Camera;
	cam->poz = c;
	c->valoare = numar;
	c->urmatorul = 0;
	if (!C.primul)
		C.primul = C.ultimul = e;
	else
	{
		C.ultimul->urmatorul = e;
		C.ultimul = e;
	}
}
void calculeazaTraseuOptimInZona(Zona Z, Solutie & S)
{
	ListaCamere L;
	L.inc = 0, L.sf = 0;
	Coordonate c = {X, Y};
	adaugaCameraInLista(L, c);
}
void initializeazaVectorDeZone(Zona Z[])
{
	Coordonate d[] = {
		{0, 0},
		{0, M-1},
		{N-1, 0},
		{N-1, M-1}
	};
	Coordonate lx[] = {
		{0, X},
		{0, X},
		{X, N-1},
		{X, N-1}
	};
	Coordonate ly[] = {
		{0, Y},
		{Y, M-1},
		{0, Y},
		{Y, M-1}
	};
	for (int i = 0; i < NR_ZONE; i++)
	{
		Z[i].dest = d[i];
		Z[i].limx = lx[i];
		Z[i].limy = ly[i];
	}
}
void citesteDateleDeIntrare()
{
	ifstream citeste("cri.in");
	citeste >> N >> M >> X >> Y;
	X--, Y--;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			citeste >> C[i][j];
	citeste.close();
}
