#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxn = 1e5 + 10, maxm = maxn;
int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
bool h[maxm << 1];
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
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

int n, m, root, MOD;

int depth[maxn], sum[maxn], hson[maxn], fa[maxn];
void dfs1(int x)
{
	sum[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			depth[to[i]] = depth[x] + 1;
			fa[to[i]] = x;
			dfs1(to[i]);
			sum[x] += sum[to[i]];
		}

	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x] && sum[to[i]] > sum[hson[x]]) hson[x] = to[i];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] == hson[x]) {h[i] = h[i ^ 1] = 1;break;}
}

int w[maxn], dfn[maxn], dfs_clock, top[maxn], wt[maxn];
void dfs2(int x, int topf)
{
	top[x] = topf;
	wt[dfn[x] = ++dfs_clock] = w[x];
	
	if (hson[x])
	{
		dfs2(hson[x], topf);
		for (register int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x] && to[i] ^ hson[x]) dfs2(to[i], to[i]);
	}
}

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
		if (l == r) s[p] = wt[l] % MOD;
		else
		{
			build(lson);
			build(rson);
			s[p] = (s[ls] + s[rs]) % MOD;
		}
	}

	void maintain(int p, int l, int r, int val) {tag[p] = (tag[p] + val) % MOD;s[p] = (s[p] + (r - l + 1) * val % MOD) % MOD;}

	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, l, r, val);
		else
		{
			if (tag[p])
			{
				maintain(lson, tag[p]);
				maintain(rson, tag[p]);
				tag[p] = 0;
			}
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			s[p] = (s[ls] + s[rs]) % MOD;
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p] ;
		else
		{
			if (tag[p])
			{
				maintain(lson, tag[p]);
				maintain(rson, tag[p]);
				tag[p]= 0;
			}
			register int res = 0;
			if (L <= mid) res = (res + query(lson, L, R)) % MOD;
			if (R >  mid) res = (res + query(rson, L, R)) % MOD;
			return res;
		}
	}
}T;
int sum1(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		ans += T.query(1, 1, n, dfn[top[x]], dfn[x]); ans %= MOD;
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return (ans + T.query(1, 1, n, dfn[x], dfn[y])) % MOD;
}

int sum2(int x)
{
	return T.query(1, 1, n, dfn[x], dfn[x] + sum[x] - 1);
}

void update1(int x, int y, int z)
{
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		T.update(1, 1, n, dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	T.update(1, 1, n, dfn[x], dfn[y], z);
}

void update2(int x, int z)
{
	T.update(1, 1, n, dfn[x], dfn[x] + sum[x] - 1, z);
}

signed main()
{
#ifdef CraZYali
	freopen("3384.in", "r", stdin);
	freopen("3384.out", "w", stdout);
#endif
	cin >> n >> m >> root >> MOD;
	REP(i, 1, n) w[i] = read<int>();
	REP(I, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	depth[root] = 1;
	dfs1(root);
	dfs2(root, root);
	T.build(1, 1, n);
	while (m --> 0)
	{
		register int opt = read<int>(), x = read<int>();
		if (opt == 1)
		{
			register int y = read<int>(), z = read<int>() % MOD;
			update1(x, y, z);
		}
		else if (opt == 2)
		{
			register int y = read<int>();
			printf("%lld\n", sum1(x, y));
		}
		else if (opt == 3)
		{
			register int z = read<int>() % MOD;
			update2(x, z);
		}
		else printf("%lld\n", sum2(x));
	}

	return 0;
}
