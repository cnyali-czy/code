/*
	Problem:	treasure.cpp
	Time:		2020-06-13 15:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 400 + 5, maxk = 17;
#define uint unsigned
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k, c;
uint p[maxk << 1], V[maxn], Z[maxn], v[maxk], z[maxk];
uint G[maxn][maxn], d0[maxn][maxn], d1[maxn][maxn], d2[maxn][maxn], d[(1 << 16) + 5][maxn], d3[maxn][maxn], ans[maxn][maxn];
bitset <maxk << 1> vis, gd;

signed main()
{
#ifdef CraZYali
	file("treasure");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	const uint inf = 1000000000;
	REP(i, 1, n) REP(j, 1, n) if (i ^ j) G[i][j] = d0[i][j] = inf;
	REP(i, 0, k + k - 1) REP(j, 1, n) d1[i][j] = inf;
	REP(i, 0, k + k - 1) REP(j, 0, k + k - 1) d2[i][j] = inf;
	REP(i, 0, k - 1) REP(j, 0, k - 1) d3[i][j] = inf;
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		chkmin(G[x][y], z);chkmin(G[y][x], z);
	}
	REP(i, 0, k - 1)
	{
		V[p[c++] = v[i] = read<int>()] |= 1 << i;
		Z[p[c++] = z[i] = read<int>()] |= 1 << i;
	}
	REP(i, 1, n) if (!V[i]) REP(j, 1, n) if (!V[j]) d0[i][j] = G[i][j];
	REP(k, 1, n) REP(i, 1, n) if (d0[i][k] < inf) REP(j, 1, n) chkmin(d0[i][j], d0[i][k] + d0[k][j]);
	REP(j, 1, n) if (!V[j]) REP(i, 0, c - 1) REP(k, 1, n) chkmin(d1[i][j], G[p[i]][k] + d0[k][j]);
	REP(i, 0, c - 1) REP(j, i, c - 1)
	{
		d2[i][j] = G[p[i]][p[j]];
		REP(k, 1, n) if (!V[k]) REP(l, 1, n) if (!V[l]) chkmin(d2[i][j], G[p[i]][k] + d0[k][l] + G[l][p[j]]);
		d2[j][i] = d2[i][j];
	}
	REP(i, 0, c - 1) d1[i][p[i]] = 0;
	REP(i, 0, k - 1)
	{
		REP(j, 0, c - 1) REP(_k, 0, (1 << k) - 1) d[_k][j] = inf;
		d[Z[z[i]]][i << 1 | 1] = 0;
		gd.set();
		REP(S, 0, (1 << k) - 1)
		{
			const int ccc = end_S ^ S;
			REP(k, 0, c - 1) vis[k] = 0;
			REP(times, 1, c)
			{
				int x = 0;
				while (vis[x]) x++;
				REP(i, x + 1, c - 1) if (!vis[i] && d[S][i] < d[S][x]) x = i;
				vis[x] = 1;
				if (d[S][x] >= inf) break;
				REP(i, 0, c - 1) if (!(ccc & V[p[i]])) chkmin(d[S | Z[p[i]]][i], d[S][x] + d2[x][i]);
			}
			REP(_k, 0, k - 1) chkmin(d3[i][_k], d[S][_k << 1]);
		}
	}
	REP(S, 1, n) if (!V[S]) REP(T, 1, n) if (S ^ T)
	{
		ans[S][T] = d0[S][T];
		REP(j, 0, k - 1) if (!V[z[j]]) REP(_k, 0, k - 1)
			chkmin(ans[S][T], d1[j << 1 | 1][S] + d3[j][_k] + d1[_k << 1][T]);
	}
	int q = read<int>();
	while (q--)
	{
		int S = read<int>(), T = read<int>();
		if (V[S]) puts("-1");
		else printf("%d\n", ans[S][T] >= inf ? -1 : ans[S][T]);
	}
	return 0;
}
