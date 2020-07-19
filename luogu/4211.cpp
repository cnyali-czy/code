#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define i64 long long

using namespace std;
const int maxn = 50000 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, q;
int fa[maxn], siz[maxn], hvy[maxn], top[maxn];

namespace fenwick
{
	i64 s1[maxn], s2[maxn];
	void add(int p, i64 val)
	{
		const i64 qaq = val * p;
		for (int i = p; i <= n; i += i & -i)
			s1[i] += val, s2[i] += qaq;
	}
	void add(int l, int r, int val)
	{
		REP(i, l, r) s1[i] += val;
//		add(l, val);
//		add(r + 1, -val);
	}
	i64 query(i64 p)
	{
		i64 res = 0;
		for (int i = p; i; i &= (i - 1))
			res += (p + 1) * s1[i] - s2[i];
		return res;
	}
	i64 query(int l, int r)
	{
		i64 res = 0;
		REP(i, l, r) res += s1[i];
		return res;
		return query(r) - query(l - 1);
	}
}
int dfn[maxn], dfs_clock;
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}
int ans[maxn];
vector <pair <int, int> > Opt[maxn];
void ins(int x)
{
	while (top[x] ^ 1)
	{
		fenwick :: add(dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
	fenwick :: add(1, dfn[x], 1);
}
i64 query(int x)
{
	i64 res = 0;
	while (top[x] ^ 1)
	{
		res += fenwick :: query(dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	return res + fenwick :: query(1, dfn[x]);
}
int main()
{
#ifdef CraZYali
	file("4211");
#endif
	n = read<int>();q = read<int>();
	REP(i, 2, n) add(fa[i] = read<int>() + 1, i);
	dfs1(1);dfs2(1, 1);
	REP(i, 1, q)
	{
		int l = read<int>() + 1, r = read<int>() + 1, z = read<int>() + 1;
		Opt[l - 1].emplace_back(-i, z);
		Opt[r].emplace_back(i, z);
	}
	REP(i, 1, n)
	{
		ins(i);
		for (auto j : Opt[i])
		{
			int id = j.first, z = j.second;
			if (id > 0)	ans[id] += query(z);
			else		ans[-id] -= query(z);
		}
	}
	REP(i, 1, q) printf("%d\n", ans[i] % 201314);
	return 0;
}
