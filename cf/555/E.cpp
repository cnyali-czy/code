/*
	Problem:	E.cpp
	Time:		2020-03-31 16:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10, maxq = 2e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
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

int n, m, q;

int dfn[maxn], low[maxn], dfs_clock;
bool ban[maxm << 1];
void tarjan(int u, int fa = 0)
{
	dfn[u] = low[u] = ++dfs_clock;
	for (int i = bg[u]; i; i = ne[i]) if (to[i] ^ fa)
		if (!dfn[to[i]])
		{
			tarjan(to[i], u);
			chkmin(low[u], low[to[i]]);
			if (low[to[i]] > dfn[u]) ban[i] = ban[i ^ 1] = 1;
		}
		else chkmin(low[u], dfn[to[i]]);
}

int blg[maxn], k;
void dfs(int x)
{
	blg[x] = k;
	for (int i = bg[x]; i; i = ne[i]) if (!ban[i] && !blg[to[i]])
		dfs(to[i]);
}

vector <int> G[maxn];
inline void Add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}
int cur, v[maxn], siz[maxn], fa[maxn], top[maxn], dep[maxn], hvy[maxn];
void dfs1(int u)
{
	v[u] = cur;
	siz[u] = 1;
	for (int v : G[u]) if (v ^ fa[u])
	{
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[v] > siz[hvy[u]]) hvy[u] = v;
	}
}
void dfs2(int u, int y)
{
	top[u] = y;
	if (!hvy[u]) return;
	dfs2(hvy[u], y);
	for (int v : G[u]) if (v ^ fa[u] && v ^ hvy[u])
		dfs2(v, v);
}
int lca(int x, int y)
{
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
int s1[maxn], s2[maxn];
bool judge(int u)
{
	for (int v : G[u]) if (v ^ fa[u])
	{
		if (!judge(v) || (s1[v] && s2[v])) return 0;
		s1[u] += s1[v];
		s2[u] += s2[v];
	}
	return 1;
}
int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) if (!dfn[i]) tarjan(i);
	REP(i, 1, n) if (!blg[i]) ++k, dfs(i);
	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i])
		if (blg[to[i]] > blg[x]) Add(blg[x], blg[to[i]]);
	REP(i, 1, k) if (!v[i])
	{
		++cur;
		dfs1(i);dfs2(i, i);
	}
	while (q--)
	{
		int x(blg[read<int>()]), y(blg[read<int>()]);
		if (x == y) continue;
		if (v[x] ^ v[y])
		{
			puts("No");
			return 0;
		}
		int l(lca(x, y));
		s1[x]++;s1[l]--;
		s2[y]++;s2[l]--;
	}
	REP(i, 1, n) if (!dep[i] && !judge(i))
	{
		puts("No");
		return 0;
	}
	puts("Yes");
	return 0;
}
