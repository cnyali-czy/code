#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxq = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int read()
{
	int x;
	scanf("%d", &x);
	return x;
}

int n, q;

int siz[maxn], top[maxn], hvy[maxn], fa[maxn], dep[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		dep[to[i]] = dep[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
int dfn[maxn], dfs_clock;
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}
int lca(int u, int v)
{
	while (top[u] ^ top[v])
	{
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;	
}
int ty[maxq], u[maxq], v[maxq], w[maxq];
int ans[maxq];

namespace fenwick
{
	int s[maxn], dfs_clock, dfn[maxn];
	inline void clear() {dfs_clock++;}
	void add(int x, int y)
	{
		while (x <= n)
		{
			if (dfn[x] ^ dfs_clock) dfn[x] = dfs_clock, s[x] = 0;
			s[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x > 0)
		{
			if (dfn[x] == dfs_clock) y += s[x];
			x &= (x - 1);
		}
		return y;
	}
	int sum(int l, int r) {return sum(r) - sum(l - 1);}
}
inline void ins(int u, int v, int flg) // insert a path from u to v
{
	fenwick :: add(dfn[u], flg);
	fenwick :: add(dfn[v], flg);
	int l = lca(u, v);
	fenwick :: add(dfn[l], -flg);
	if (fa[l]) fenwick :: add(dfn[fa[l]], -flg);
}
inline int cnt(int u) // count how many paths went through u
{
	return fenwick :: sum(dfn[u], dfn[u] + siz[u] - 1);
}

void work(int l, int r, vector <int> vec)
{
	if (l > r || !vec.size()) return;
	int mid = l + r + 1 >> 1;
	fenwick :: clear();
	int N = 0;
	vector <int> lft, rit;
	for (auto i : vec)
		if (ty[i] == 0)
			if (w[i] >= mid) N++, ins(u[i], v[i],  1), rit.emplace_back(i);
			else lft.emplace_back(i);
		else if (ty[i] == 1)
			if (w[i] >= mid) N--, ins(u[i], v[i], -1), rit.emplace_back(i);
			else lft.emplace_back(i);
		else if (ty[i] == 2)
			if (!N || cnt(w[i]) == N) lft.emplace_back(i);
			else ans[i] = mid, rit.emplace_back(i);
	if (l == r) return;
	work(l, mid - 1, lft);
	work(mid, r, rit);
}

int main()
{
#ifdef CraZYali
	freopen("3250.in", "r", stdin);
	freopen("3250.out", "w", stdout);
#endif
	n = read();q = read();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	int fk = 0;
	REP(i, 1, q)
	{
		ty[i] = read();
		if (!ty[i]) u[i] = read(), v[i] = read(), w[i] = read(), fk = max(fk, w[i]);
		else if (ty[i] == 1)
		{
			int t = read();
			u[i] = u[t];
			v[i] = v[t];
			w[i] = w[t];
		}
		else w[i] = read();
	}
	REP(i, 1, q) ans[i] = -1;
	vector <int> vec(q);REP(i, 1, q) vec[i - 1] = i;
	work(1, fk, vec);
	REP(i, 1, q) if (ty[i] == 2) printf("%d\n", ans[i]);
	return 0;
}
