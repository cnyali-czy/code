/*
	Problem:	mis.cpp
	Time:		2020-06-13 21:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 400 + 5;
int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, w[maxn], siz[maxn];
i64 f[maxn][maxn], g[maxn][maxn], h[maxn];
const i64 inf = 1e15;
void dfs(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
	REP(i, 0, n) f[x][i] = g[x][i] = -inf;
	REP(p, 1, n)
	{
		REP(i, 0, n) h[i] = -inf;
		h[1] = 1ll * p * w[x];
		for (int i = bg[x]; i; i = ne[i])
		{
			int v = to[i];
			DEP(j, p, 1) if (h[j] > -(inf / 2))
			{
				REP(k, j + 1, min(p, j + siz[v])) chkmax(h[k], h[j] + g[v][k - j]);
				h[j] += f[v][p];
			}
		}
		chkmax(g[x][p], h[p]);
		REP(j, 1, p) chkmax(f[x][j], h[p - j]);
	}
}
int main()
{
#ifdef CraZYali
	file("mis");
#endif
	n = read<int>();
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n) add(read<int>(), i);
	dfs(1);
	i64 ans = g[1][1];
	REP(i, 2, n) chkmax(ans, g[1][i]);
	cout << ans << endl;
	return 0;
}
