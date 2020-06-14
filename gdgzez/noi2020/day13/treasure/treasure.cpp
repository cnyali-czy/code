/*
	Problem:	treasure.cpp
	Time:		2020-06-13 15:22
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bitset>
#include <cassert>
#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 400 + 5, maxk = 17;
#define uint unsigned
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
int read()
{
	int ans = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k, c;
uint p[maxk << 1], V[maxn], Z[maxn], v[maxk], z[maxk];
uint G[maxn][maxn], d0[maxn][maxn], d1[maxn][maxn], d2[maxn][maxn], d[(1 << 16) + 5][maxn], d3[maxn][maxn], ans[maxn][maxn];
bitset <maxk << 1> vis, gd;
int tmp[maxn], ttt;
void write(int x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + 48);
}
inline void chkmin(uint &x, uint y) {if (x > y) x = y;}
signed main()
{
#ifdef CraZYali
	file("treasure");
#endif
	n = read();m = read();k = read();
	const uint inf = 1000000000;
	REP(i, 1, n) REP(j, 1, n) if (i ^ j) G[i][j] = d0[i][j] = inf;
	REP(i, 0, k + k - 1) REP(j, 1, n) d1[i][j] = inf;
	REP(i, 0, k + k - 1) REP(j, 0, k + k - 1) d2[i][j] = inf;
	REP(i, 0, k - 1) REP(j, 0, k - 1) d3[i][j] = inf;
	REP(i, 1, m)
	{
		int x(read()), y(read()), z(read());
		chkmin(G[x][y], z);chkmin(G[y][x], z);
	}
	REP(i, 0, k - 1)
	{
		V[p[c++] = v[i] = read()] |= 1 << i;
		Z[p[c++] = z[i] = read()] |= 1 << i;
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
		REP(_k, 0, (1 << k) - 1) 
			REP(j, 0, c - 1) 
			d[_k][j] = inf;
		d[Z[z[i]]][i << 1 | 1] = 0;
		REP(S, 0, (1 << k) - 1)
		{
			const int ccc = end_S ^ S;
			gd.set();
			ttt = 0;
			REP(i, 0, c - 1) if (!(ccc & V[p[i]])) tmp[++ttt] = i;
			REP(times, 1, c)
			{
				int x = gd._Find_first();
				for (int i = gd._Find_next(x); i < c; i = gd._Find_next(i))
					if (d[S][i] < d[S][x]) x = i;
				gd[x] = 0;
				if (d[S][x] >= inf) break;
				REP(j, 1, ttt) {int i = tmp[j];chkmin(d[S | Z[p[i]]][i], d[S][x] + d2[x][i]);}
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
	int q = read();
	while (q--)
	{
		int S = read(), T = read();
		if (V[S] || ans[S][T] >= inf) puts("-1");
		else write(ans[S][T]), putchar(10);
	}
	return 0;
}
