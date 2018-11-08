#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

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

template <typename T> inline T read()
{
	T ans(0), p(1);
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k, rt, MOD;

int w[maxn], wt[maxn], depth[maxn], dfn[maxn], dfs_clock, fa[maxn], siz[maxn], hson[maxn], top[maxn];

void dfs1(int x)
{
	siz[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			depth[to[i]] = depth[x] + 1;
			fa[to[i]] = x;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hson[x]]) hson[x] = to[i];
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
int mod(int x) {if (x < 0) return (x % MOD + MOD) % MOD;return x >= MOD ? x % MOD : x;}

#define ls p << 1 
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
struct SMT
{
	int s[maxn << 2], tag[maxn << 2];
	void build(int p, int l, int r)
	{
		if (l == r) s[p] = wt[l];
		else
		{
			build(lson);
			build(rson);
			s[p] = mod(s[ls] + s[rs]);
		}
	}
	void maintain(int p, int l, int r, int val)
	{
		s[p] = mod(s[p] + mod(mod(r - l + 1) * val));
		tag[p] = mod(tag[p] + val);
	}
	void pushdown(int p, int l, int r)
	{
		if (tag[p])
		{
			maintain(lson, tag[p]);
			maintain(rson, tag[p]);
			tag[p] = 0;
		}
	}
	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, l, r, val);
		else
		{
			pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			s[p] = mod(s[ls] + s[rs]);
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			pushdown(p, l, r);
			if (L >  mid) return query(rson, L, R);
			if (R <= mid) return query(lson, L, R);
			return mod(query(lson, L, R) + query(rson, L, R));
		}
	}
}T;

void update1(int x, int y, int z)
{
	z %= MOD;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		T.update(1, 1, n, dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	T.update(1, 1, n, dfn[x], dfn[y], z);
}

int query1(int x, int y)
{
	int ret = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		ret = mod(ret + T.query(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return mod(ret + T.query(1, 1, n, dfn[x], dfn[y]));
}
void update2(int x, int z) {T.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, z % MOD);}
int query2(int x) {return T.query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1);}

signed main()
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
	dfs1(rt);
	dfs2(rt, rt);
	T.build(1, 1, n);
	while (m --> 0)
	{
		register int opt = read<int>(), x = read<int>();
		if (opt == 1)
		{
			register int y = read<int>(), z = read<int>();
			update1(x, y, z);
		}
		else if (opt == 2) printf("%lld\n", query1(x, read<int>()));
		else if (opt == 3) update2(x, read<int>());
		else printf("%lld\n", query2(x));
	}
	return 0;
}
