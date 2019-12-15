#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
const int maxn = 2e5 + 10, maxN = maxn * 80;

template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, fa[maxn], c[maxn], d[maxn];

int ls[maxN], rs[maxN], s[maxN], cur, rt[maxn], ans[maxn], lp[maxn], rp[maxn];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
const int inf = 2e11;
void update(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	s[p] += val;
	if (l == r) return;
	if (pos <= mid) update(lson, pos, val);
	else			update(rson, pos, val);
}
int merge(int x, int y)
{
	if (!x || !y) return x + y;
	s[x] += s[y];
	ls[x] = merge(ls[x], ls[y]);
	rs[x] = merge(rs[x], rs[y]);
	return x;
}
int del_l(int p, int l, int r, int s)
{
	if (!s) return 0;
	::s[p] -= s;
	if (l == r) return l;
	if (s <= ::s[ls[p]]) return del_l(lson, s);
	else
	{
		s -= ::s[ls[p]];
		ls[p] = 0;
		return del_l(rson, s);
	}
}
int del_r(int p, int l, int r, int s)
{
	if (!s) return 0;
	::s[p] -= s;
	if (l == r) return l;
	if (s <= ::s[rs[p]]) return del_r(rson, s);
	else
	{
		s -= ::s[rs[p]];
		rs[p] = 0;
		return del_r(lson, s);
	}
}
int query(int p, int l, int r, int pos)
{
	if (l == r) return l;
	if (s[ls[p]] >= pos)	return query(lson, pos);
	else					return query(rson, pos - s[ls[p]]);
}
int sum[maxn];
void dfs(int x, int dep)
{
	if (bg[x])
	{
		for (int i = bg[x]; i; i = ne[i])
		{
			dfs(to[i], dep + c[to[i]]);
			sum[x] += sum[to[i]];
			rt[x] = merge(rt[x], rt[to[i]]);
		}
		lp[x] = rp[x] = -1;
		if ((x ^ 1) && sum[x] > d[x])
		{
			lp[x] = del_l(rt[x], 0, inf, sum[x] - d[x]);
			rp[x] = del_r(rt[x], 0, inf, sum[x] - d[x]);
			sum[x] = d[x];
		}
	}
	else
	{
		sum[x] = d[x];
		lp[x] = rp[x] = dep;
		update(rt[x], 0, inf, dep, d[x] * 2);
	}
}
void deal(int x, int res)
{
	if (x ^ 1)
	{
		ans[x] = c[x];
		if (~lp[x])
		{
			if (res < lp[x]) ans[x] -= lp[x] - res, res = lp[x];
			if (res > rp[x]) ans[x] += res - rp[x], res = rp[x];
		}
	}
	for (int i = bg[x]; i; i = ne[i]) deal(to[i], res);
}
signed main()
{
#ifdef CraZYali
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		add(fa[i] = read<int>(), i);
		c[i] = read<int>();d[i] = read<int>();
	}
	dfs(1, 0);
	int Left(query(rt[1], 0, inf, sum[1]));
	deal(1, Left);
	int ans(0);
	REP(i, 2, n) ans += abs(::ans[i] - c[i]) * d[i];
	printf("%lld\n", ans);
	REP(i, 2, n) printf("%lld\n", ::ans[i]);
	return 0;
}
