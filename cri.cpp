#include <fstream>
#define MAX_N 500
#define MAX_M 500
#define NR_ZONE 4
#define NR_DIRECTII 4
using namespace std;
struct Coordonate { int x, y; };
struct Zona { Coordonate destinatie, limitaLinie, limitaColoana; };
struct Solutie { int Z, T, K; };
int directieOx[] = {-1, 0, 1, 0};
int directieOy[] = {0, 1, 0, -1};
int N, M, X, Y, C[MAX_N][MAX_M];
void citesteDateleDeIntrare();
void initializeazaVectorDeZone(Zona*);
void initializeazaVectorDeSolutii(Solutie*);
void calculeazaSolutie(int, Coordonate, Zona, Solutie &);
void calculeazaRezultat(Solutie*, Solutie &);
int main()
{
    Zona z[NR_ZONE];
    Solutie s[NR_ZONE], sol;
	citesteDateleDeIntrare();
	initializeazaVectorDeZone(z);
	initializeazaVectorDeSolutii(s);
	for (int i = 0; i < NR_ZONE; i++)
        calculeazaSolutie(1, {X, Y}, z[i], s[i]);
	calculeazaRezultat(s, sol);
	ofstream scrie("cri.out");
	scrie << sol.Z << ' ' << sol.T << ' ' << sol.K;
	scrie.close();
	return 0;
}
void calculeazaRezultat(Solutie s[], Solutie & sol)
{
    sol.T = 0;
    sol.K = N*M;
	for (int i = 0; i < NR_ZONE; i++)
    {
        if (s[i].T > sol.T)
            sol = s[i];
        else if (s[i].T == sol.T && s[i].K < sol.K)
            sol = s[i];
    }
}
bool esteCameraInZona(Coordonate c, Zona z)
{
    return c.x >= z.limitaLinie.x && c.x <= z.limitaLinie.y
        && c.y >= z.limitaColoana.x && c.y <= z.limitaColoana.y;
}
bool esteCameraNevizitata(Coordonate c)
{
    return C[c.x][c.y] >= 0;
}
bool potVizitaCamera(Coordonate c, Zona z)
{
    if (!esteCameraInZona(c, z))
        return 0;
    return esteCameraNevizitata(c);
}
bool suntCoordonateleEgale(Coordonate a, Coordonate b)
{
    return a.x == b.x && a.y == b.y;
}
void calculeazaSolutie(int pas, Coordonate c, Zona z, Solutie & s)
{
    if (suntCoordonateleEgale(c, z.destinatie))
    {
        if (C[c.x][c.y] > s.T)
        {
            s.T = C[c.x][c.y];
            s.K = pas;
        }
        else if (C[c.x][c.y] == s.T)
            if (pas < s.K)
                s.K = pas;
    }
    else
        for (int i = 0; i < NR_DIRECTII; i++)
        {
            Coordonate vecin;
            vecin.x = c.x + directieOx[i];
            vecin.y = c.y + directieOy[i];
            if (potVizitaCamera(vecin, z))
            {
                int graunteC = C[c.x][c.y];
                int graunteV = C[vecin.x][vecin.y];
                C[vecin.x][vecin.y] += graunteC;
                C[c.x][c.y] = -1;
                calculeazaSolutie(pas+1, vecin, z, s);
                C[c.x][c.y] = graunteC;
                C[vecin.x][vecin.y] = graunteV;
            }
        }
}
void initializeazaVectorDeSolutii(Solutie s[])
{
    for (int i = 0; i < NR_ZONE; i++)
    {
        s[i].Z = i+1;
        s[i].T = 0;
        s[i].K = N*M;
    }
}
void initializeazaVectorDeZone(Zona z[])
{
	Coordonate destinatie[] = {
		{0, 0},
		{0, M-1},
		{N-1, 0},
		{N-1, M-1}
	};
	Coordonate limitaLinie[] = {
		{0, X},
		{0, X},
		{X, N-1},
		{X, N-1}
	};
	Coordonate limitaColoana[] = {
		{0, Y},
		{Y, M-1},
		{0, Y},
		{Y, M-1}
	};
	for (int i = 0; i < NR_ZONE; i++)
	{
		z[i].destinatie = destinatie[i];
		z[i].limitaLinie = limitaLinie[i];
		z[i].limitaColoana = limitaColoana[i];
	}
}
void citesteDateleDeIntrare()
{
	ifstream citeste("cri.in");
	citeste >> N >> M >> X >> Y;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			citeste >> C[i][j];
    X--, Y--; // deoarece indicii pornesc de la 0
	citeste.close();
}
