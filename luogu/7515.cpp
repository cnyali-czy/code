/*
	Problem:	7515.cpp
	Time:		2021-04-16 10:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define poly vector <int>

using namespace std;
const int maxn = 300 + 5, L = 1e6;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, b[maxn][maxn], N = 0;
poly E[maxn][maxn];

inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator - (poly f, poly g)
{
	f.resize(max(f.size(), g.size()));
	REP(i, 0, deg(g)) f[i] -= g[i];
	return f;
}

int X[maxn][maxn], Y[maxn][maxn], Z[maxn][maxn], C[maxn][maxn];

int sgn[maxn << 1];

int main()
{
#ifdef CraZYali
	file("7515");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n - 1) REP(j, 1, m - 1) b[i][j] = read<int>();
		REP(i, 1, n) REP(j, 1, m) E[i][j].clear(), E[i][j].resize(n + m - 1);
	
		N = 0;
		E[1][1][++N] = 1;
		REP(i, 2, m) E[1][i][++N] = 1;
		REP(i, 2, n) E[i][1][++N] = 1;
		/*
		 * 1 2 3 ... m - 2 m - 1 m
		 * m + 1
		 * m + 2
		 * ...
		 * n + m - 2
		 * n + m - 1
		 * */
		REP(i, 2, n) REP(j, 2, m)
			E[i][j] = poly{b[i - 1][j - 1]} - E[i - 1][j] - E[i][j - 1] - E[i - 1][j - 1];
		REP(i, 1, N) sgn[i] = 1;
		REP(i, 2, n) REP(j, 2, m)
		{
			//a[i][j] = X[i][j] * a[1][1] + Y[i][j] * a[1][j] + Z[i][j] * a[i][1] + C[i][j]
			X[i][j] = E[i][j][1];
			Y[i][j] = E[i][j][j];
			Z[i][j] = E[i][j][m + i - 1];
			C[i][j] = E[i][j][0];
			int x = X[i][j], y = Y[i][j], z = Z[i][j], c = C[i][j];
			//0 <= x * a1 + y * a[1][j] + z * a[i][1] + c <= L
			if (x < 0)
			{
				x = -x;
				y = -y;
				z = -z;
				c = L - c;
			}
			if (y < 0) sgn[j] = -1;
			if (z < 0) sgn[i - 1 + m] = -1;
		}
		cerr << '\n';
	}
	return 0;
}
