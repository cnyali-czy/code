/*
	Problem:	D.cpp
	Time:		2020-10-17 22:24
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

using namespace std;
const int maxn = 1000 + 10, maxq = 1000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
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

int n, q;
int u[maxn], v[maxn];

bool col[maxn];


int dep[maxn], fa[maxn];
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dfs(to[i]);
	}
}
int lca(int x, int y)
{
	if (dep[x] < dep[y]) swap(x, y);
	while (dep[x] > dep[y]) x = fa[x];
	if (x == y) return x;
	while (x ^ y) x = fa[x], y = fa[y];
	return x;
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		u[i] = read<int>();v[i] = read<int>();
		add(u[i], v[i]);add(v[i], u[i]);
	}
	q = read<int>();
	while (q--)
	{
		int opt = read<int>(), x = read<int>(), y = read<int>();
		if (opt == 1)
		{
		}
	}
	return 0;
}
