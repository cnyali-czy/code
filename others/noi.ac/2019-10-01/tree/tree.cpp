#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, q;

int dfn[maxn], dfs_clock, fa[maxn], top[maxn], siz[maxn], hvy[maxn], depth[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa[x])
	{
		depth[to[i]] = depth[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}

namespace violence
{
	const int maxn = 1000 + 10;
	int dis[maxn][maxn], l[maxn][maxn];
	inline int lca(int x, int y)
	{
		while (top[x] ^ top[y])
		{
			if (depth[top[x]] < depth[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return depth[x] < depth[y] ? x : y;
	}
	long long w[maxn];
	inline void add_link(int x, int y, int v)
	{
		int qaq = l[x][y];
		while (x ^ qaq)
		{
			w[x] += v;
			x = fa[x];
		}
		while (y ^ qaq)
		{
			w[y] += v;
			y = fa[y];
		}
		w[qaq] += v;
	}
	void add_chld(int x, int v)
	{
		w[x] += v;
		for (int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa[x])
			add_chld(to[i], v);
	}
	inline void mul_link(int x, int y, int t, long long v)
	{
		int qaq = l[x][y];
		while (x ^ qaq)
		{
			w[x] += v * dis[x][t];
			x = fa[x];
		}
		while (y ^ qaq)
		{
			w[y] += v * dis[y][t];
			y = fa[y];
		}
		w[qaq] += v * dis[qaq][t];
	}
	void mul_chld(int x, int t, long long v)
	{
		w[x] += v * dis[x][t];
		for (int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa[x])
			mul_chld(to[i], t, v);
	}
	inline long long sum_link(int x, int y)
	{
		long long res(0);
		int qaq = l[x][y];
		while (x ^ qaq)
		{
			res += w[x];
			x = fa[x];
		}
		while (y ^ qaq)
		{
			res += w[y];
			y = fa[y];
		}
		return res + w[qaq];
	}
	long long sum_chld(int x)
	{
		long long res(w[x]);
		for (int i(bg[x]); i; i = ne[i]) if (to[i] ^ fa[x])
			res += sum_chld(to[i]);
		return res;
	}
	void work()
	{
		REP(i, 1, n)
			REP(j, i, n)
				dis[i][j] = dis[j][i] = depth[i] + depth[j] - 2 * depth[l[i][j] = l[j][i] = lca(i, j)];
		while (q--)
		{
			int opt, x, y, t, v;
			scanf("%d%d", &opt, &x);
			if (opt == 1)
			{
				scanf("%d%d", &y, &v);
				add_link(x, y, v);
			}
			else if (opt == 2)
			{
				scanf("%d", &v);
				add_chld(x, v);
			}
			else if (opt == 3)
			{
				scanf("%d%d%d", &y, &t, &v);
				mul_link(x, y, t, v);
			}
			else if (opt == 4)
			{
				scanf("%d%d", &t, &v);
				mul_chld(x, t, v);
			}
			else if (opt == 5) printf("%lld\n", w[x]);
			else if (opt == 6)
			{
				scanf("%d", &y);
				printf("%lld\n", sum_link(x, y));
			}
			else printf("%lld\n", sum_chld(x));
		}
	}
};

namespace dalishupou
{
	long long sum[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	inline void pushup(int p)
	{
		sum[p] = sum[ls] + sum[rs];
	}
	inline void maintain(int p, int l, int r, long long val)
	{
		sum[p] += val * (r - l + 1);
		tag[p] += val;
	}
	inline void pushdown(int p, int l, int r)
	{
		if (!tag[p]) return;
		maintain(lson, tag[p]);
		maintain(rson, tag[p]);
		tag[p] = 0;
	}
	void update(int p, int l, int r, int L, int R, long long val)
	{
		if (L <= l && r <= R) maintain(p, l, r, val);
		else
		{
			pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			pushup(p);
		}
	}
	long long query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return sum[p];
		else
		{
			pushdown(p, l, r);
			if (L >  mid) return query(rson, L, R);
			if (R <= mid) return query(lson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
	inline void add_link(int x, int y, int v)
	{
		while (top[x] ^ top[y])
		{
			if (depth[top[x]] < depth[top[y]]) swap(x, y);
			update(1, 1, n, dfn[top[x]], dfn[x], v);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y]) swap(x, y);
		update(1, 1, n, dfn[x], dfn[y], v);
	}
	inline void add_chld(int x, int v) {update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, v);}
	inline void mul_link(int x, int y, int t, long long v)
	{
	}
	inline void mul_chld(int x, int y, long long v)
	{
	}
	inline long long query_point(int x)
	{
		return query(1, 1, n, dfn[x], dfn[x]);
	}
	inline long long sum_link(int x, int y)
	{
		long long res(0);
		while (top[x] ^ top[y])
		{
			if (depth[top[x]] < depth[top[y]]) swap(x, y);
			res += query(1, 1, n, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y]) swap(x, y);
		return res + query(1, 1, n, dfn[x], dfn[y]);
	}
	inline long long sum_chld(int x) {return query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1);}
	void work()
	{
		while (q--)
		{
			int opt, x, y, t, v;
			scanf("%d%d", &opt, &x);
			if (opt == 1)
			{
				scanf("%d%d", &y, &v);
				add_link(x, y, v);
			}
			else if (opt == 2)
			{
				scanf("%d", &v);
				add_chld(x, v);
			}
			else if (opt == 3)
			{
				scanf("%d%d%d", &y, &t, &v);
				mul_link(x, y, t, v);
			}
			else if (opt == 4)
			{
				scanf("%d%d", &t, &v);
				mul_chld(x, t, v);
			}
			else if (opt == 5) printf("%lld\n", query_point(x));
			else if (opt == 6)
			{
				scanf("%d", &y);
				printf("%lld\n", sum_link(x, y));
			}
			else printf("%lld\n", sum_chld(x));
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	dfs1(1);
	dfs2(1, 1);
	cin >> q;
	if (n <= 1000 && q <= 1000) violence::work();
	else dalishupou::work();
	return 0;
}
