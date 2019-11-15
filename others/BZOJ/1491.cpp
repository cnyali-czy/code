/*
 * File Name:	1491.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.15 08:46
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m;

const int inf = 1e9;
int G[maxn][maxn];
long long c[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("1491");
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
		REP(j, 1, n) G[i][j] = inf;
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		G[x][y] = G[y][x] = read<int>();
		c[x][y] = c[y][x] = 1;
	}
	REP(k, 1, n)
		REP(i, 1, n) if (G[i][k] < inf)
		REP(j, 1, n) if (G[k][j] < inf && i != j)
			if (G[i][j] > G[i][k] + G[k][j])
			{
				G[i][j] = G[i][k] + G[k][j];
				c[i][j] = c[i][k] * c[k][j];
			}
			else if (G[i][j] == G[i][k] + G[k][j])
				c[i][j] += c[i][k] * c[k][j];
	REP(v, 1, n)
	{
		double res(0);
		REP(s, 1, n) if (s ^ v)
			REP(t, 1, n) if (t ^ v)
				if (G[s][t] == G[s][v] + G[v][t]) res += 1. * c[s][v] * c[v][t] / c[s][t];
		printf("%.3lf\n", res);
	}
	return 0;
}
