#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, rt, MOD;
int w[maxn], wt[maxn], dfn[maxn], dfs_clock, son[maxn], hson[maxn], depth[maxn], fa[maxn], top[maxn];
void dfs1(int x)
{
	son[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			son[x] += son[to[i]];
			if (son[to[i]] >= son[hson[x]]) hson[x] = to[i];
		}
}
void dfs2(int x, int y)
{
	wt[dfn[x] = ++dfs_clock] = w[x];
	top[x] = y;
	if (hson[x])
	{
		dfs2(hson[x], y);
		for (register int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x] && to[i] ^ hson[x]) dfs2(to[i], to[i]);
	}
}

int sum[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void build(int p, int l, int r)
{
	if (l == r) sum[p] = wt[l] % MOD;
	else
	{
		build(lson);
		build(rson);
		sum[p] = (sum[ls] + sum[rs]) % MOD;
	}
}

void maintain(int p, int l, int r, int val)
{
	tag[p] = (tag[p] + val) % MOD;
	sum[p] = (sum[p] + val * (r - l + 1)) % MOD;
}

void pushdown(int p, int l, int r) {maintain(lson, tag[p]);maintain(rson, tag[p]);tag[p] = 0;}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) sum[p] = (sum[p] + (r - l + 1) * val % MOD) % MOD, tag[p] = (tag[p] + val) % MOD;
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		sum[p] = (sum[ls] + sum[rs]) % MOD;
	}
}

int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return (query(lson, L, R) + query(rson, L, R)) % MOD;
	}
}

void update1(int x, int y, int z)
{
	z %= MOD;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		update(1, 1, n, dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	update(1, 1, n, dfn[x], dfn[y], z);
}

int sum2(int x, int y)
{
	int z = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		z = (z + query(1, 1, n, dfn[top[x]], dfn[x])) % MOD;
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return (z + query(1, 1, n, dfn[x], dfn[y])) % MOD;
}

void update3(int x, int z){update(1, 1, n, dfn[x], dfn[x] + son[x] - 1, z);}
int sum4(int x) {return query(1, 1, n, dfn[x], dfn[x] + son[x] - 1);}

int main()
{
#ifdef CraZYali
	freopen("3384-new.in", "r", stdin);
	freopen("3384-new.out", "w", stdout);
#endif
	cin >> n >> m >> rt >> MOD;
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	depth[rt] = 1;
	dfs1(rt);dfs2(rt, rt);
	build(1, 1, n);
	while (m --> 0)
	{
		register int ty = read<int>(), x = read<int>();
		if (ty == 1) {register int y = read<int>(), z = read<int>();update1(x, y, z);}
		else if (ty == 2) {register int y = read<int>();printf("%d\n", sum2(x, y));}
		else if (ty == 3) {register int z = read<int>();update3(x, z);}
		else printf("%d\n", sum4(x));
	}
	return 0;
}
