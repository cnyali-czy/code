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

	hson[x] = -1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x] && sum[to[i]] > sum[hson[x]]) hson[x] = to[i];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] == hson[x]) {h[i] = h[i ^ 1] = 1;break;}
}

int w[maxn], wt[maxn], dfn[maxn], dfs_clock, top[maxn];
void dfs2(int x, int topf)
{
	top[x] = topf;
	dfn[x] = ++dfs_clock;
	wt[dfn[x]] = w[x];
	if (hson[x] != -1)
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
		if (l == r) s[p] = wt[l] ;
		else
		{
			build(lson);
			build(rson);
			s[p] = (s[ls] + s[rs]) % MOD;
		}
	}

	void maintain(int p, int l, int r, int val) {s[p] = (s[p] + (r - l + 1) * val % MOD) % MOD;}

	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R)
		{
			s[p] = (s[p] + val) % MOD;
			tag[p] = (tag[p] + val) % MOD;
		}
		else
		{
			if (tag[p])
			{
				maintain(lson, tag[p]);
				maintain(rson, tag[p]);
				tag[p]= 0;
			}
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			s[p] = (s[ls] + s[rs]) % MOD;
		}
	}
	int sum(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (tag[p])
			{
				maintain(lson, tag[p]);
				maintain(rson, tag[p]);
				tag[p]= 0;
			register int res = 0;
			if (L <= mid) res = (res + sum(lson, L, R)) % MOD;
			if (R >  mid) res = (res + sum(rson, L, R)) % MOD;
			return res;
		}
	}
}T;
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
	

	return 0;
}
