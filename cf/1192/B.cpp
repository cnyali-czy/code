/*
	Problem:	B.cpp
	Time:		2021-01-04 08:58
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
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, W, x[maxn], y[maxn], z[maxn];

int siz[maxn], fa[maxn], dep[maxn], hvy[maxn], down[maxn], dis[maxn], wfa[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dis[to[i]] = dis[x] + w[i];
		wfa[down[i >> 1] = to[i]] = w[i];
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
int dl[maxn], dfs_clock, back[maxn], dr[maxn], top[maxn];
void dfs2(int x, int y)
{
	dl[x] = ++dfs_clock;dr[x] = dl[x] + siz[x] - 1;
	back[dfs_clock] = x;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}

namespace fenwick
{
	int s[maxn];
	void add(int x, int y)
	{
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
	void add(int l, int r, int v)
	{
		add(l, v);
		add(r + 1, -v);
	}
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
int dist(int x, int y) {return fenwick :: sum(dl[x]) + fenwick :: sum(dl[y]) - 2 * fenwick :: sum(dl[lca(x, y)]);}

namespace SMT
{
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define fi first
#define se second
	pair <int, int> t[maxn << 2];
	void pushup(int p)
	{
		int a[] = {t[ls].fi, t[ls].se, t[rs].fi, t[rs].se}, d = 0;
		REP(i, 0, 3) REP(j, i + 1, 3)
		{
			int cur = dist(a[i], a[j]);
			if (cur >= d)
			{
				d = cur;
				t[p] = make_pair(a[i], a[j]);
			}
		}
	}
	void build(int p, int l, int r)
	{
		if (l == r) t[p] = make_pair(back[l], back[l]);
		else
		{
			build(lson);
			build(rson);
			pushup(p);
		}
	}
	void fix(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return;
		else
		{
			if (L <= mid) fix(lson, L, R);
			if (R >  mid) fix(rson, L, R);
			pushup(p);
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();W = read<int>();
	REP(i, 1, n - 1)
	{
		x[i] = read<int>();y[i] = read<int>();z[i] = read<int>();
		add(x[i], y[i], z[i]);
		add(y[i], x[i], z[i]);
	}
	dfs1(1);dfs2(1, 1);
	REP(i, 1, n) fenwick :: add(dl[i], dl[i], dis[i]);
	SMT :: build(1, 1, n);
	int lstans = 0;
	while (q--)
	{
		int D = (read<int>() + lstans) % (n - 1) + 1;
		int E = (read<int>() + lstans) % W;
		int x = down[D];
		fenwick :: add(dl[x], dr[x], E - wfa[x]);
		wfa[x] = E;
		SMT :: fix(1, 1, n, dl[x], dr[x]);
		printf("%lld\n", lstans = dist(SMT :: t[1].fi, SMT :: t[1].se));
	}
	return 0;
}
