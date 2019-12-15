#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5, maxm = 100 + 5;

inline int read()
{
	int x;
	scanf("%d", &x);
	return x;
}

int a[maxn][maxm], n, m, q;
inline void right(int r)
{
	int x = a[r][m];
	DREP(i, m - 1, 1) a[r][i+1] = a[r][i];
	a[r][1] = x;
}
inline void down(int c)
{
	int x = a[n][c];
	DREP(i, n - 1, 1) a[i+1][c] = a[i][c];
	a[1][c] = x;
}

int opt[10005], r[10005], c[10005], x[10005];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	REP(i, 1, q)
	{
		opt[i] = read();
		if (opt[i] == 1) r[i] = read();
		else if (opt[i] == 2) c[i] = read();
		else
		{
			r[i] = read();
			c[i] = read();
			x[i] = read();
		}
	}
	DREP(i, q, 1)
		if (opt[i] == 1) right(r[i]);
		else if (opt[i] == 2) down(c[i]);
		else a[r[i]][c[i]] = x[i];
	REP(i, 1, n)
		REP(j, 1, m)
		printf("%d%c", a[i][j], j == m ? '\n' : ' ');
	return 0;
}
