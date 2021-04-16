#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10, MOD = 998244353;
inline int read() {int x;scanf("%d", &x);return x;}

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int bin2[maxn];
void init(int n)
{
	bin2[0] = 1;
	REP(i, 1, n) bin2[i] = bin2[i - 1] * 2 % MOD;
}

int n, q, u[maxn], v[maxn];

int fa[maxn], siz[maxn], hvy[maxn], dep[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
int top[maxn], dfn[maxn], dfs_clock;
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
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
inline bool cmp(int x, int y) {return dfn[x] < dfn[y];}

int main()
{
#ifdef CraZYali
	freopen("6773-new.in", "r", stdin);
	freopen("6773-new.out", "w", stdout);
#endif
	n = read();init(n);
	REP(i, 1, n - 1)
	{
		int x = read(), y = read();
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	q = read();
	REP(i, 1, q) u[i] = read(), v[i] = read();
	i64 ans = 0;
	REP(S, 0, (1 << q) - 1)
	{
		static int vec[maxn];int m = 0;
		REP(i, 1, q) if (S >> (i - 1) & 1) vec[++m] = u[i], vec[++m] = v[i];
		sort(vec + 1, vec + 1 + m, cmp);m = unique(vec + 1, vec + 1 + m) - vec - 1;
		REP(i, 2, m) vec[++m] = lca(vec[i], vec[i - 1]);
		sort(vec + 1, vec + 1 + m, cmp);m = unique(vec + 1, vec + 1 + m) - vec - 1;

		int marked = 0;
		static int cnt[maxn];
		REP(i, 1, m) cnt[vec[i]] = 0;

		REP(i, 1, q) if (S >> (i - 1) & 1) cnt[u[i]]--, cnt[v[i]]++;
		DEP(i, m, 2)
		{
			int fa = lca(vec[i - 1], vec[i]);
			if (cnt[vec[i]]) marked += dep[vec[i]] - dep[fa];
			cnt[fa] += cnt[vec[i]];
		}
		int fk = n - 1 - marked;

		ans += ((__builtin_popcount(S) & 1) ? MOD - bin2[fk] : bin2[fk]);
	}
	cout << ans % MOD << endl;
	return 0;
}
