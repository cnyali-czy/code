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

int m, n, k, rt;

int w[maxn], wt[maxn], depth[maxn], dfn[maxn], dfs_clock, fa[maxn], siz[maxn], hson[maxn], top[maxn];

void dfs1(int x)
{
	hson[x] = 0;
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

#define ls p << 1 
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
struct SMT
{
	int s[maxn << 2], Max[maxn << 2], Min[maxn << 2];
	void pushup(int p, int l, int r)
	{
		s[p] = (s[ls] + s[rs]);
		Max[p] = max(Max[ls], Max[rs]);
		Min[p] = min(Min[ls], Min[rs]);
	}
	void build(int p, int l, int r)
	{
		if (l == r) Max[p] = Min[p] = s[p] = wt[l];
		else
		{
			build(lson);
			build(rson);
			pushup(p, l, r);
		}
	}
	int sol(int p, int l, int r, int a, int b, int L, int R)
	{
		if (L <= l && r <= R)
		{
			if (a <= Min[p] && Max[p] <= b) return s[p];
			if (Min[p] > b || Max[p] < a) return 0;
		}
		if (L >  mid) return sol(rson, a, b, L, R);
		if (R <= mid) return sol(lson, a, b, L, R);
		return sol(lson, a, b, L, R) + sol(rson, a, b, L, R);
	}
}T;

int solve(int a, int b, int x, int y)
{
	int ret = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		ret += T.sol(1, 1, n, a, b, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (x == y) return (ret + w[x] * (a <= w[x] && w[x] <= b));
	if (depth[x] > depth[y]) swap(x, y);
	return (ret + T.sol(1, 1, n, a, b, dfn[x], dfn[y]));
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	rt = 1;
	while (scanf("%lld %lld", &n, &m) != EOF)
	{
		dfs_clock = 0;
		e = 1;
		REP(i, 1, n) w[i] = read<int>(), bg[i] = 0 ;
		REP(i, 2, n)
		{
			register int x = read<int>(), y = read<int>();
			add(x, y);add(y, x);
		}
		depth[rt] = 1;
		dfs1(rt);
		dfs2(rt, rt);
		T.build(1, 1, n);
		REP(i, 1, m)
		{
			register int x = read<int>(), y = read<int>(), a = read<int>(), b = read<int>();
			printf("%lld%c", solve(a, b, x, y), i == m ? '\n' : ' ');
		}
	}
	return 0;
}
