/*
	Problem:	C.cpp
	Time:		2020-02-15 19:29
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
#define uint unsigned int
using namespace std;
const int maxn = 3e5 + 10;

int deg[maxn], bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
{
	deg[x]++;deg[y]++;
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

int n, m;
int fa[maxn];

uint f[maxn];

int c2[maxn], siz[maxn];
uint grandson[maxn], son[maxn], self[maxn], pre[maxn], init[maxn], hvy[maxn], up[maxn];

void dfs(int x)
{
	uint fir = init[x];
	siz[x] = 1;
	c2[x] = deg[x] + (!fa[x]);
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		c2[x] += deg[to[i]] - 1;
		init[x] += init[to[i]];
	}
	up[x] = siz[x] - siz[hvy[x]];
	grandson[x] = siz[x] + 1;
	son[x] = siz[x] + 1;
	self[x] = siz[x] + 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		son[x] += siz[x] - siz[to[i]];
		self[x] += (uint)(siz[x] - siz[to[i]]) * deg[to[i]];
		pre[x] += init[to[i]] * (siz[x] - siz[to[i]] - 1);
	}
	pre[x] += init[x] + fir * siz[x];
}
int top[maxn], dfn[maxn], dfs_clock;
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
}

uint c[maxn];
void ins(int x, uint y)
{
	while (x <= n) c[x] += y, x += x & -x;
}
uint sum(int x)
{
	uint res = 0;
	while (x > 0) res += c[x], x &= (x - 1);
	return res;
}

uint w[maxn], _less[maxn];
void Add(int x, uint val)
{
	w[x] += val;
	val *= c2[x];
	while (top[x])
	{
		_less[fa[top[x]]] += val * (siz[fa[top[x]]] - siz[top[x]]);
		ins(dfn[top[x]], val);
		ins(dfn[x],		-val);
		x = fa[top[x]];
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	REP(i, 1, n) init[i] = read<int>();
	dfs(1);dfs2(1, 1);
	while (m--)
	{
		int opt = read<int>(), x = read<int>();
		if (opt == 1) Add(x, read<uint>());
		else printf("%u\n", w[fa[fa[x]]] * grandson[x] + w[fa[x]] * son[x] + w[x] * self[x] + up[x] * sum(dfn[x]) + _less[x] + pre[x]);
	}
	return 0;
}
