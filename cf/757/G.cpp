#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int n, q;
int p[maxn];

int siz[maxn], fa[maxn], top[maxn], hvy[maxn], dfn[maxn], back[maxn], dfs_clock;
i64 dis[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dis[to[i]] = dis[x] + w[i];
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	back[dfn[x] = ++dfs_clock] = x;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
}

namespace SMT
{
	const int maxN = 2e7;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	int ls[maxN], rs[maxN], cur;
	i64 s[maxN], t[maxN], xs[maxN];
	void init()
	{
		REP(i, 1, n)
		{
			int x = back[i];
			xs[i] = xs[i - 1] + dis[x] - dis[fa[x]];
		}
	}
	void update(int pre, int &p, int l, int r, int L, int R, int val)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		s[p] = s[pre];
		t[p] = t[pre];
		if (L <= l && r <= R)
		{
			s[p] += (xs[r] - xs[l - 1]) * val;
			t[p] += val;
		}
		else
		{
			if (L <= mid) update(ls[pre], lson, L, R, val);
			if (R >  mid) update(rs[pre], rson, L, R, val);
			s[p] = s[ls[p]] + s[rs[p]];
		}
	}
	i64 query(int p, int l, int r, int L, int R)
	{
		if (!p) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			i64 res = t[p] * (xs[R] - xs[L - 1]);
			if (L <= mid) res += query(lson, L, min(R, mid));
			if (R >  mid) res += query(rson, max(mid + 1, L), R);
			return res;
		}
	}
}
int rt[maxn];
void orz(int pre, int &p, int x)
{
	p = pre;
	while (x)
	{
		SMT :: update(p, p, 1, n, dfn[top[x]], dfn[x], 1);
		x = fa[top[x]];
	}
}

int main()
{
#ifdef CraZYali
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
#endif
	cin >> n >> q;
	REP(i, 1, n) scanf("%d", p + i);
	REP(i, 2, n)
	{
		int x, y, z;scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);add(y, x, z);
	}
	dfs1(1);dfs2(1, 1);
	SMT :: init();
	REP(i, 1, n) orz(rt[i - 1], rt[i], p[i]);
	while (q--)
	{
		int opt;scanf("%d", &opt);
		if (opt == 1)
		{
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			printf("%lld\n", query(
		}
		else
		{
		}
	}
	return 0;
}
